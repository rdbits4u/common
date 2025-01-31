const std = @import("std");

//const g_check_check = false;
const g_check_check = true;
const g_num_layers = 4;

pub const parse_t = struct
{
    allocator: *const std.mem.Allocator = undefined,
    data: []u8 = undefined,
    offset: usize = 0,
    check_offset: usize = 0,
    layer_offsets: [g_num_layers]usize = .{0} ** g_num_layers,
    did_alloc: bool = false,

    //*************************************************************************
    pub fn delete(self: *parse_t) void
    {
        if (self.did_alloc)
        {
            self.allocator.free(self.data);
        }
        self.allocator.destroy(self);
    }

    //*************************************************************************
    pub fn reset(self: *parse_t, size: usize) !void
    {
        if (self.did_alloc)
        {
            if (size > self.data.len)
            {
                self.allocator.free(self.data);
                self.data = try self.allocator.alloc(u8, size);
            }
        }
        else
        {
            if (size > self.data.len)
            {
                return error.InvalidParam;
            }
        }
        self.offset = 0;
        self.check_offset = 0;
    }

    //*************************************************************************
    pub fn get_out_slice(self: *parse_t) []u8
    {
        return self.data[0..self.offset];
    }

    //*************************************************************************
    pub fn check_rem_bool(self: *parse_t, size: usize) bool
    {
        self.check_offset = self.offset + size;
        return self.offset + size <= self.data.len;
    }

    //*************************************************************************
    pub fn check_rem(self: *parse_t, size: usize) !void
    {
        if (!self.check_rem_bool(size))
        {
            return error.NoRoom;
        }
    }

    //*************************************************************************
    pub inline fn out_u8(self: *parse_t, val: u8) void
    {
        var offset = self.offset;
        self.data[offset] = val;
        offset += 1;
        self.offset = offset;
        check_check(self, @src().fn_name);
    }

    //*************************************************************************
    pub inline fn out_i8(self: *parse_t, val: i8) void
    {
        out_u8(self, @bitCast(val));
    }

    //*************************************************************************
    pub inline fn out_u16_le(self: *parse_t, val: u16) void
    {
        var offset = self.offset;
        self.data[offset] = @truncate(val);
        offset += 1;
        self.data[offset] = @truncate(val >> 8);
        offset += 1;
        self.offset = offset;
        check_check(self, @src().fn_name);
    }

    //*************************************************************************
    pub inline fn out_u16_be(self: *parse_t, val: u16) void
    {
        var offset = self.offset;
        self.data[offset] = @truncate(val >> 8);
        offset += 1;
        self.data[offset] = @truncate(val);
        offset += 1;
        self.offset = offset;
        check_check(self, @src().fn_name);
    }

    //*************************************************************************
    pub inline fn out_i16_le(self: *parse_t, val: i16) void
    {
        return out_u16_le(self, @bitCast(val));
    }

    //*************************************************************************
    pub inline fn out_i16_be(self: *parse_t, val: i16) void
    {
        return out_u16_be(self, @bitCast(val));
    }

    //*************************************************************************
    pub inline fn out_u32_le(self: *parse_t, val: u32) void
    {
        var offset = self.offset;
        self.data[offset] = @truncate(val);
        offset += 1;
        self.data[offset] = @truncate(val >> 8);
        offset += 1;
        self.data[offset] = @truncate(val >> 16);
        offset += 1;
        self.data[offset] = @truncate(val >> 24);
        offset += 1;
        self.offset = offset;
        check_check(self, @src().fn_name);
    }

    //*************************************************************************
    pub inline fn out_u32_be(self: *parse_t, val: u32) void
    {
        var offset = self.offset;
        self.data[offset] = @truncate(val >> 24);
        offset += 1;
        self.data[offset] = @truncate(val >> 16);
        offset += 1;
        self.data[offset] = @truncate(val >> 8);
        offset += 1;
        self.data[offset] = @truncate(val);
        offset += 1;
        self.offset = offset;
        check_check(self, @src().fn_name);
    }

    //*************************************************************************
    pub inline fn out_i32_le(self: *parse_t, val: i32) void
    {
        out_u32_le(self, @bitCast(val));
    }

    //*************************************************************************
    pub inline fn out_i32_be(self: *parse_t, val: i32) void
    {
        out_u32_be(self, @bitCast(val));
    }

    //*************************************************************************
    pub inline fn out_u64_le(self: *parse_t, val: u64) void
    {
        out_u32_le(self, @truncate(val));
        out_u32_le(self, @truncate(val >> 32));
    }

    //*************************************************************************
    pub inline fn out_u64_be(self: *parse_t, val: u64) void
    {
        out_u32_be(self, @truncate(val >> 32));
        out_u32_be(self, @truncate(val));
    }

    //*************************************************************************
    pub inline fn out_i64_le(self: *parse_t, val: i64) void
    {
        out_u64_le(self, @bitCast(val));
    }

    //*************************************************************************
    pub inline fn out_i64_be(self: *parse_t, val: i64) void
    {
        out_u64_be(self, @bitCast(val));
    }

    //*************************************************************************
    pub fn out_u8_slice(self: *parse_t, slice: []const u8) void
    {
        var offset = self.offset;
        for (slice) |byte|
        {
            self.data[offset] = byte;
            offset += 1;
        }
        self.offset = offset;
        check_check(self, @src().fn_name);
    }

    //*************************************************************************
    pub fn out_u8_skip(self: *parse_t, bytes: usize) void
    {
        var offset = self.offset;
        var index: usize = 0;
        while (index < bytes)
        {
            self.data[offset] = 0;
            offset += 1;
            index += 1;
        }
        self.offset = offset;
        check_check(self, @src().fn_name);
    }

    //*************************************************************************
    pub inline fn in_u8(self: *parse_t) u8
    {
        var offset = self.offset;
        const rv: u8 = self.data[offset];
        offset += 1;
        self.offset = offset;
        check_check(self, @src().fn_name);
        return rv;
    }

    //*************************************************************************
    pub inline fn in_u16_le(self: *parse_t) u16
    {
        var offset = self.offset;
        var rv: u16 = self.data[offset];
        offset += 1;
        const rv1: u16 = self.data[offset];
        offset += 1;
        rv = rv | (rv1 << 8);
        self.offset = offset;
        check_check(self, @src().fn_name);
        return rv;
    }

    //*************************************************************************
    pub inline fn in_u16_be(self: *parse_t) u16
    {
        var offset = self.offset;
        var rv: u16 = self.data[offset];
        offset += 1;
        rv = (rv << 8) | self.data[offset];
        offset += 1;
        self.offset = offset;
        check_check(self, @src().fn_name);
        return rv;
    }

    //*************************************************************************
    pub inline fn in_i16_le(self: *parse_t) i16
    {
        return @bitCast(in_u16_le(self));
    }

    //*************************************************************************
    pub inline fn in_i16_be(self: *parse_t) i16
    {
        return @bitCast(in_u16_be(self));
    }

    //*************************************************************************
    pub inline fn in_u32_le(self: *parse_t) u32
    {
        var offset = self.offset;
        var rv: u32 = self.data[offset];
        offset += 1;
        const rv1: u32 = self.data[offset];
        offset += 1;
        const rv2: u32 = self.data[offset];
        offset += 1;
        const rv3: u32 = self.data[offset];
        offset += 1;
        rv = rv | (rv1 << 8) | (rv2 << 16) | (rv3 << 24);
        self.offset = offset;
        check_check(self, @src().fn_name);
        return rv;
    }

    //*************************************************************************
    pub inline fn in_u32_be(self: *parse_t) u32
    {
        var offset = self.offset;
        var rv: u32 = self.data[offset];
        offset += 1;
        rv = (rv << 8) | self.data[offset];
        offset += 1;
        rv = (rv << 8) | self.data[offset];
        offset += 1;
        rv = (rv << 8) | self.data[offset];
        offset += 1;
        self.offset = offset;
        check_check(self, @src().fn_name);
        return rv;
    }

    //*************************************************************************
    pub inline fn in_i32_le(self: *parse_t) i32
    {
        return @bitCast(in_u32_le(self));
    }

    //*************************************************************************
    pub inline fn in_i32_be(self: *parse_t) i32
    {
        return @bitCast(in_u32_be(self));
    }

    //*************************************************************************
    pub inline fn in_u64_le(self: *parse_t) u64
    {
        const rv: u64 = in_u32_le(self);
        const rv1: u64 = in_u32_le(self);
        return rv | (rv1 << 32);
    }

    //*************************************************************************
    pub inline fn in_u64_be(self: *parse_t) u64
    {
        const rv: u64 = in_u32_be(self);
        return (rv << 32) | in_u32_be(self);
    }

    //*************************************************************************
    pub inline fn in_i64_le(self: *parse_t) i64
    {
        return @bitCast(in_u64_le(self));
    }

    //*************************************************************************
    pub inline fn in_i64_be(self: *parse_t) i64
    {
        return @bitCast(in_u64_be(self));
    }

    //*************************************************************************
    pub fn in_u8_slice(self: *parse_t, bytes: usize) []u8
    {
        var offset = self.offset;
        const end = offset + bytes;
        const slice: []u8 = self.data[offset..end];
        offset += bytes;
        self.offset = offset;
        check_check(self, @src().fn_name);
        return slice;
    }

    //*************************************************************************
    pub fn in_u8_skip(self: *parse_t, bytes: usize) void
    {
        var offset = self.offset;
        offset += bytes;
        self.offset = offset;
        check_check(self, @src().fn_name);
    }

    //*************************************************************************
    pub fn push_layer(self: *parse_t, bytes: usize, layer: u8) void
    {
        var offset = self.offset;
        self.layer_offsets[layer] = offset;
        offset += bytes;
        self.offset = offset;
        check_check(self, @src().fn_name);
    }

    //*************************************************************************
    pub fn pop_layer(self: *parse_t, layer: u8) void
    {
        self.offset = self.layer_offsets[layer];
    }

    //*************************************************************************
    pub fn layer_subtract(self: *parse_t, a: usize, b: usize) u16
    {
         return @truncate(self.layer_offsets[a] - self.layer_offsets[b]);
    }

};

//*****************************************************************************
pub fn create(allocator: *const std.mem.Allocator, size: usize) !*parse_t
{
    const self: *parse_t = try allocator.create(parse_t);
    errdefer allocator.destroy(self);
    self.* = .{};
    self.allocator = allocator;
    self.data = try allocator.alloc(u8, size);
    self.did_alloc = true;
    return self;
}

//*****************************************************************************
pub fn create_from_slice(allocator: *const std.mem.Allocator,
        slice: []u8) !*parse_t
{
    const self: *parse_t = try allocator.create(parse_t);
    self.* = .{};
    self.allocator = allocator;
    self.data = slice;
    self.did_alloc = false;
    return self;
}

//*****************************************************************************
inline fn check_check(self: *parse_t, fn_name: []const u8) void
{
    if (g_check_check and (self.check_offset < self.offset))
    {
        std.debug.print("check_check: {s}\n", .{fn_name});
    }
}
