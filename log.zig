const std = @import("std");
const builtin = @import("builtin");

pub const LogLevel = enum(u8)
{
    always = 0,
    err,
    warning,
    info,
    debug,
    trace,
    never,
};

const g_log_lv_names = [_][]const u8
{
    "ALLWAYS",
    "ERROR",
    "WARNING",
    "INFO",
    "DEBUG",
    "TRACE",
    "NEVER",
};

// run time log level
var g_lv: LogLevel = LogLevel.debug;
var g_allocator: *const std.mem.Allocator = undefined;
var g_seconds_bias: i32 = 0;
var g_bias_str: [8:0]u8 = .{'+', '0', '0', '0', '0', 0, 0, 0};
var g_name: [32:0] u8 = .{'U', 'T', 'C'} ++ .{0} ** (32 - 3);
const g_max_name_len = 6; // size of std.tz.Timetype.name_data
const g_show_devel = false;
var g_file: ?std.fs.File = null;

//*****************************************************************************
pub fn init(allocator: *const std.mem.Allocator, lv: LogLevel) !void
{
    g_allocator = allocator;
    g_lv = lv;
    const result = init_timezone();
    if (result) |_|
    {
        // ok
        try logln(LogLevel.info, @src(),
                "logging init ok, time zone [{s}] [{s}]",
                .{std.mem.sliceTo(&g_name, 0),
                std.mem.sliceTo(&g_bias_str, 0)});
    }
    else |err|
    {
        try logln(LogLevel.err, @src(),
                "init_timezone failed err {}", .{err});
    }
}

//*****************************************************************************
pub fn initWithFile(allocator: *const std.mem.Allocator, lv: LogLevel,
        file_name: []const u8) !void
{
    if (file_exists(file_name))
    {
        const save_file_name = try std.fmt.allocPrint(g_allocator.*,
                "{s}.last", .{file_name});
        defer g_allocator.free(save_file_name);
        try std.posix.rename(file_name, save_file_name);
    }
    const file = try std.fs.createFileAbsolute(file_name, .{});
    g_file = file;
    try init(allocator, lv);
    try logln(LogLevel.info, @src(), "logging file name [{s}]", .{file_name});
}

//*****************************************************************************
fn file_exists(file_path: []const u8) bool
{
    const mode = std.posix.F_OK;
    std.posix.access(file_path, mode) catch
        return false;
    return true;
}

const TIME_ZONE_ID_UNKNOWN: u32 = 0;
const TIME_ZONE_ID_STANDARD: u32 = 1;
const TIME_ZONE_ID_DAYLIGHT: u32 = 2;
const TIME_ZONE_ID_INVALID: u32 = 4294967295;

const SYSTEMTIME = extern struct
{
    wYear: u16,
    wMonth: u16,
    wDayOfWeek: u16,
    wDay: u16,
    wHour: u16,
    wMinute: u16,
    wSecond: u16,
    wMilliseconds: u16,
};
const TIME_ZONE_INFORMATION = extern struct
{
    Bias: i32,
    StandardName: [32]u16,
    StandardDate: SYSTEMTIME,
    StandardBias: i32,
    DaylightName: [32]u16,
    DaylightDate: SYSTEMTIME,
    DaylightBias: i32,
};

extern "kernel32"
fn GetTimeZoneInformation(lpTimeZoneInformation: ?*TIME_ZONE_INFORMATION)
        callconv(std.os.windows.WINAPI) u32;

const CP_UTF8: u32 = 65001;

const WC_COMPOSITECHECK: u32 = 0x00000200;

extern "kernel32"
fn WideCharToMultiByte(CodePage: u32, dwFlags: u32,
    lpWideCharStr: [*:0]const u16, cchWideChar: i32,
    lpMultiByteStr: ?[*]u8, cbMultiByte: i32, lpDefaultChar: ?[*]const u8,
    lpUsedDefaultChar: ?*i32,) callconv(std.os.windows.WINAPI) i32;

//*****************************************************************************
fn time_zone_name(out: [:0]u8, in: []const u16) !void
{
    const lin = in[0..in.len :0];
    _ = WideCharToMultiByte(CP_UTF8, WC_COMPOSITECHECK,
            lin.ptr, @intCast(lin.len),
            out.ptr, @intCast(out.len), null, null);
}

//*****************************************************************************
// setup g_seconds_bias, g_bias_str, g_name
fn init_timezone() !void
{
    if (builtin.target.os.tag == .windows)
    {
        var tzi: TIME_ZONE_INFORMATION = undefined;
        const rv = GetTimeZoneInformation(&tzi);
        if (rv != TIME_ZONE_ID_INVALID)
        {
            g_seconds_bias = tzi.Bias * -60;
            if (rv == TIME_ZONE_ID_STANDARD)
            {
                try time_zone_name(&g_name, &tzi.StandardName);
            }
            else if (rv == TIME_ZONE_ID_DAYLIGHT)
            {
                g_seconds_bias += 60 * 60;
                try time_zone_name(&g_name, &tzi.DaylightName);
            }
            const sign: u8 = if (g_seconds_bias < 0) '-' else '+';
            _ = try std.fmt.bufPrintZ(&g_bias_str, "{c}{d:0>4.0}",
                    .{sign, @abs(@divTrunc(g_seconds_bias, 36))});
        }
        return;
    }
    const zoneinfo = "/usr/share/zoneinfo/";
    var tz_file_path: ?[]u8 = null;
    const tz_env = std.posix.getenv("TZ");
    if (tz_env) |atz_env|
    {
        if (atz_env[0] == '/')
        {
            tz_file_path = try std.fmt.allocPrint(g_allocator.*, "{s}",
                    .{atz_env});
        }
        else
        {
            tz_file_path = try std.fmt.allocPrint(g_allocator.*, "{s}{s}",
                    .{zoneinfo, atz_env});
        }
    }
    else if (file_exists("/etc/timezone"))
    {
        const file = try std.fs.openFileAbsolute("/etc/timezone",
                .{.mode = .read_only});
        defer file.close();
        var buf_reader = std.io.bufferedReader(file.reader());
        const in_stream = buf_reader.reader();
        const buf = try g_allocator.alloc(u8, 1024);
        defer g_allocator.free(buf);
        if (try in_stream.readUntilDelimiterOrEof(buf, '\n')) |line|
        {
            tz_file_path = try std.fmt.allocPrint(g_allocator.*, "{s}{s}",
                    .{zoneinfo, line});
        }
    }
    else if (file_exists("/etc/localtime"))
    {
        tz_file_path = try std.fmt.allocPrint(g_allocator.*,
                "/etc/localtime", .{});
    }
    if (tz_file_path) |atz_file_path|
    {
        defer g_allocator.free(atz_file_path);
        const file = try std.fs.openFileAbsolute(atz_file_path,
                .{.mode = .read_only});
        defer file.close();
        var buf_reader = std.io.bufferedReader(file.reader());
        const in_stream = buf_reader.reader();
        var tz = try std.Tz.parse(g_allocator.*, in_stream);
        defer tz.deinit();
        // time in seconds
        const now = std.time.timestamp();
        var last: ?std.tz.Transition = null;
        for (tz.transitions) |trans|
        {
            if (trans.ts > now)
            {
                break;
            }
            last = trans;
        }
        if (last) |alast|
        {
            g_seconds_bias = alast.timetype.offset;
            const name = alast.timetype.name();
            var index: usize = 0;
            while (index < g_max_name_len) : (index += 1)
            {
                g_name[index] = name[index];
                if (g_name[index] == 0)
                {
                    break;
                }
            }
            const sign: u8 = if (g_seconds_bias < 0) '-' else '+';
            _ = try std.fmt.bufPrintZ(&g_bias_str, "{c}{d:0>4.0}",
                    .{sign, @abs(@divTrunc(g_seconds_bias, 36))});
        }
    }
}

//*****************************************************************************
pub fn deinit() void
{
    if (g_file) |afile|
    {
        afile.close();
    }
}

//*****************************************************************************
pub fn logln(lv: LogLevel, src: std.builtin.SourceLocation,
        comptime fmt: []const u8, args: anytype) !void
{
    const lv_int = @intFromEnum(lv);
    if (lv_int <= @intFromEnum(g_lv))
    {
        const msg_buf = try std.fmt.allocPrint(g_allocator.*,
                fmt, args);
        defer g_allocator.free(msg_buf);
        var dt: DateTime = undefined;
        // time in milliseconds
        const now = std.time.milliTimestamp();
        fromMilliTimestamp(now + g_seconds_bias * 1000, &dt);
        // date
        const date_buf = try std.fmt.allocPrint(g_allocator.*,
                // year      month     day
                "{d:0>4.0}-{d:0>2.0}-{d:0>2.0}",
                .{dt.year, dt.month, dt.day});
        defer g_allocator.free(date_buf);
        // time
        const time_buf = try std.fmt.allocPrint(g_allocator.*,
                // hour      minute    second    milliseconds
                "{d:0>2.0}:{d:0>2.0}:{d:0>2.0}.{d:0>3.0}",
                .{dt.hour, dt.minute, dt.second, dt.millisecond});
        defer g_allocator.free(time_buf);
        const log_lv_name = g_log_lv_names[lv_int];
        if (g_file) |afile|
        {
            var writer = afile.writer();
            try writer.print("[{s}T{s}{s}] [{s: <7.0}] {s}: {s}\n",
                    .{date_buf, time_buf, std.mem.sliceTo(&g_bias_str, 0),
                    log_lv_name, src.fn_name, msg_buf});
        }
        else
        {
            var writer = std.io.getStdOut().writer();
            try writer.print("[{s}T{s}{s}] [{s: <7.0}] {s}: {s}\n",
                    .{date_buf, time_buf, std.mem.sliceTo(&g_bias_str, 0),
                    log_lv_name, src.fn_name, msg_buf});
        }
    }
}

//*****************************************************************************
pub fn logln_devel(lv: LogLevel, src: std.builtin.SourceLocation,
        comptime fmt: []const u8, args: anytype) !void
{
    if (g_show_devel)
    {
        try logln(lv, src, fmt, args);
    }
}

const DateTime = struct
{
    year: u16,
    month: u8,
    day: u8,
    hour: u8,
    minute: u8,
    second: u8,
    millisecond: u16,
};

//*****************************************************************************
fn fromMilliTimestamp(mst: i64, dt: *DateTime) void
{
    const MILLISECONDS_PER_DAY = 86400 * 1000;
    const DAYS_PER_YEAR = 365;
    const DAYS_IN_4YEARS = 1461;
    const DAYS_IN_100YEARS = 36524;
    const DAYS_IN_400YEARS = 146097;
    const DAYS_BEFORE_EPOCH = 719468;

    const mstu: u64 = @intCast(mst);
    const miliseconds_since_midnight: u64 = @rem(mstu, MILLISECONDS_PER_DAY);
    var day_n: u64 = DAYS_BEFORE_EPOCH + mstu / MILLISECONDS_PER_DAY;
    var temp: u64 = 0;

    temp = 4 * (day_n + DAYS_IN_100YEARS + 1) / DAYS_IN_400YEARS - 1;
    var year: u16 = @intCast(100 * temp);
    day_n -= DAYS_IN_100YEARS * temp + temp / 4;

    temp = 4 * (day_n + DAYS_PER_YEAR + 1) / DAYS_IN_4YEARS - 1;
    year += @intCast(temp);
    day_n -= DAYS_PER_YEAR * temp + temp / 4;

    var month: u8 = @intCast((5 * day_n + 2) / 153);
    const day: u8 =
            @intCast(day_n - (@as(u64, @intCast(month)) * 153 + 2) / 5 + 1);

    month += 3;
    if (month > 12)
    {
        month -= 12;
        year += 1;
    }

    dt.year = year;
    dt.month = month;
    dt.day = day;
    dt.hour = @intCast((miliseconds_since_midnight / 1000) / 3600);
    dt.minute = @intCast((miliseconds_since_midnight / 1000) % 3600 / 60);
    dt.second = @intCast((miliseconds_since_midnight / 1000) % 60);
    dt.millisecond = @intCast(miliseconds_since_midnight % 1000);
}