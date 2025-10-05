const std = @import("std");
const builtin = @import("builtin");
const expect = std.testing.expect;

//*****************************************************************************
fn my_utf8Decode2(slice: []const u8) !u21
{
    if (slice.len < 2) return error.Unexpected;
    if ((builtin.zig_version.major == 0) and (builtin.zig_version.minor == 13))
    {
        return std.unicode.utf8Decode2(slice);
    }
    else
    {
        var str2: [2]u8 = undefined;
        str2[0] = slice[0];
        str2[1] = slice[1];
        return std.unicode.utf8Decode2(str2);
    }
}

//*****************************************************************************
fn my_utf8Decode3(slice: []const u8) !u21
{
    if (slice.len < 3) return error.Unexpected;
    if ((builtin.zig_version.major == 0) and (builtin.zig_version.minor == 13))
    {
        return std.unicode.utf8Decode3(slice);
    }
    else
    {
        var str3: [3]u8 = undefined;
        str3[0] = slice[0];
        str3[1] = slice[1];
        str3[2] = slice[2];
        return std.unicode.utf8Decode3(str3);
    }
}

//*****************************************************************************
fn my_utf8Decode4(slice: []const u8) !u21
{
    if (slice.len < 4) return error.Unexpected;
    if ((builtin.zig_version.major == 0) and (builtin.zig_version.minor == 13))
    {
        return std.unicode.utf8Decode4(slice);
    }
    else
    {
        var str4: [4]u8 = undefined;
        str4[0] = slice[0];
        str4[1] = slice[1];
        str4[2] = slice[2];
        str4[3] = slice[3];
        return std.unicode.utf8Decode4(str4);
    }
}

//*****************************************************************************
pub fn utf8_to_u32_array(allocator: *const std.mem.Allocator,
        utf8_in: []const u8, utf32_out: *std.ArrayListUnmanaged(u32)) !void
{
    var in_index: usize = 0;
    const in_count = utf8_in.len;
    while (in_index < in_count)
    {
        var chr21: u21 = undefined;
        const in_bytes =
                try std.unicode.utf8ByteSequenceLength(utf8_in[in_index]);
        if (in_index + in_bytes > in_count)
        {
            return error.Unexpected;
        }
        const in_start = in_index;
        const in_end = in_start + in_bytes;
        chr21 = switch (in_bytes)
        {
            1 => utf8_in[in_index],
            2 => try my_utf8Decode2(utf8_in[in_start..in_end]),
            3 => try my_utf8Decode3(utf8_in[in_start..in_end]),
            4 => try my_utf8Decode4(utf8_in[in_start..in_end]),
            else => return error.Unexpected,
        };
        in_index += in_bytes;
        try utf32_out.append(allocator.*, chr21);
    }
    // remove any trailing zeros
    while ((utf32_out.items.len > 0) and
            (utf32_out.items[utf32_out.items.len - 1] == 0))
    {
        utf32_out.items.len -= 1;
    }
}

//*****************************************************************************
pub fn utf16_to_u32_array(allocator: *const std.mem.Allocator,
        utf16_in: []const u16, utf32_out: *std.ArrayListUnmanaged(u32)) !void
{
    var in_index: usize = 0;
    const in_count = utf16_in.len;
    while (in_index < in_count)
    {
        var chr21: u21 = undefined;
        const in_shorts =
                try std.unicode.utf16CodeUnitSequenceLength(utf16_in[in_index]);
        if (in_index + in_shorts > in_count)
        {
            return error.Unexpected;
        }
        const in_start = in_index;
        const in_end = in_start + in_shorts;
        chr21 = switch (in_shorts)
        {
            1 => utf16_in[in_index],
            2 => try std.unicode.utf16DecodeSurrogatePair(utf16_in[in_start..in_end]),
            else => return error.Unexpected,
        };
        in_index += in_shorts;
        try utf32_out.append(allocator.*, chr21);
    }
    // remove any trailing zeros
    while ((utf32_out.items.len > 0) and
            (utf32_out.items[utf32_out.items.len - 1] == 0))
    {
        utf32_out.items.len -= 1;
    }
}

//*****************************************************************************
pub fn utf16_as_u8_to_u32_array(allocator: *const std.mem.Allocator,
        utf8_in: []const u8, utf32_out: *std.ArrayListUnmanaged(u32)) !void
{
    var in_index: usize = 0;
    const in_count = utf8_in.len / 2;
    while (in_index < in_count)
    {
        var chr21: u21 = undefined;
        var utf16_in: [2]u16 = undefined;
        utf16_in[0] = utf8_in[in_index * 2 + 1];
        utf16_in[0] = (utf16_in[0] << 8) | utf8_in[in_index * 2 + 0];
        const in_shorts =
                try std.unicode.utf16CodeUnitSequenceLength(utf16_in[0]);
        if (in_index + in_shorts > in_count)
        {
            return error.Unexpected;
        }
        if (in_shorts == 1)
        {
            chr21 = utf16_in[0];
        }
        else if (in_shorts == 2)
        {
            utf16_in[1] = utf8_in[in_index * 2 + 3];
            utf16_in[1] = (utf16_in[1] << 8) | utf8_in[in_index * 2 + 2];
            chr21 = try std.unicode.utf16DecodeSurrogatePair(utf16_in[0..2]);
        }
        else
        {
            return error.Unexpected;
        }
        in_index += in_shorts;
        try utf32_out.append(allocator.*, chr21);
    }
    // remove any trailing zeros
    while ((utf32_out.items.len > 0) and
            (utf32_out.items[utf32_out.items.len - 1] == 0))
    {
        utf32_out.items.len -= 1;
    }
}

//*****************************************************************************
// counts the nil at the end
pub fn u32_array_to_utf8Z(u32_array: *std.ArrayListUnmanaged(u32),
        utf8: []u8, bytes_written_out: *usize) !void
{
    if (utf8.len < 1)
    {
        return error.Unexpected;
    }
    var lbytes_written_out: usize = 0;
    var chr21: u21 = undefined;
    var out_index: usize = 0;
    const out_max = utf8.len;
    var in_index: usize = 0;
    const in_count = u32_array.items.len;
    while (in_index < in_count) : (in_index += 1)
    {
        chr21 = @truncate(u32_array.items[in_index]);
        const bytes_out = try std.unicode.utf8CodepointSequenceLength(chr21);
        if (out_index + bytes_out > out_max)
        {
            return error.NoRoom;
        }
        const bytes_out1 = try std.unicode.utf8Encode(chr21, utf8[out_index..]);
        if (bytes_out != bytes_out1)
        {
            return error.Unexpected;
        }
        out_index += bytes_out;
        lbytes_written_out += bytes_out;
    }
    if (out_index + 1 > out_max)
    {
        return error.NoRoom;
    }
    utf8[out_index] = 0;
    bytes_written_out.* = lbytes_written_out + 1;
}

//*****************************************************************************
// counts the nil at the end
pub fn u32_array_to_utf16Z_as_u8(u32_array: *std.ArrayListUnmanaged(u32),
        utf16_as_u8: []u8, bytes_written_out: *usize) !void
{
    if ((utf16_as_u8.len >> 1) < 1)
    {
        return error.Unexpected;
    }
    var lbytes_written_out: usize = 0;
    var chr21: u21 = undefined;
    var out_index: usize = 0;
    const out_max = utf16_as_u8.len >> 1;
    var in_index: usize = 0;
    const in_count = u32_array.items.len;
    while (in_index < in_count) : (in_index += 1)
    {
        chr21 = @truncate(u32_array.items[in_index]);
        if (chr21 < 0x10000)
        {
            if (out_index + 1 > out_max)
            {
                return error.NoRoom;
            }
            utf16_as_u8[out_index * 2] = @truncate(chr21);
            utf16_as_u8[out_index * 2 + 1] = @truncate(chr21 >> 8);
            out_index += 1;
            lbytes_written_out += 2;
        }
        else
        {
            if (out_index + 2 > out_max)
            {
                return error.NoRoom;
            }
            const high = @as(u16, @intCast((chr21 - 0x10000) >> 10)) + 0xD800;
            const low = @as(u16, @intCast(chr21 & 0x3FF)) + 0xDC00;
            utf16_as_u8[out_index * 2] = @truncate(low);
            utf16_as_u8[out_index * 2 + 1] = @truncate(low >> 8);
            utf16_as_u8[out_index * 2 + 2] = @truncate(high);
            utf16_as_u8[out_index * 2 + 3] = @truncate(high >> 8);
            out_index += 2;
            lbytes_written_out += 4;
        }
    }
    if (out_index + 1 > out_max)
    {
        return error.NoRoom;
    }
    utf16_as_u8[out_index * 2] = 0;
    utf16_as_u8[out_index * 2 + 1] = 0;
    bytes_written_out.* = lbytes_written_out + 2;
}

//*****************************************************************************
// writes out string including nil at end but does not include the nil in cbSize
pub fn utf8_to_utf16Z_as_u8(allocator: *const std.mem.Allocator,
        u32_array: *std.ArrayListUnmanaged(u32),
        utf8: []const u8, utf16_as_u8: []u8, cbSize: *u16) !void
{
    try u32_array.resize(allocator.*, 0);
    try utf8_to_u32_array(allocator, utf8, u32_array);
    var bytes_written_out: usize = 0;
    try u32_array_to_utf16Z_as_u8(u32_array, utf16_as_u8, &bytes_written_out);
    cbSize.* = @truncate(bytes_written_out - 2);
}

//*****************************************************************************
// copy slice to slice but make sure dst has a nil at end
pub fn copyZ(dst: []u8, src: []const u8) void
{
    if (dst.len < 1)
    {
        return;
    }
    var index: usize = 0;
    while ((index < src.len) and (index + 1 < dst.len)) : (index += 1)
    {
        dst[index] = src[index];
    }
    dst[index] = 0;
}

//*****************************************************************************
test "copyZ"
{
    var dest: [10]u8 = .{0xAE} ** 10;
    copyZ(dest[0..1], "hello");
    try expect(std.mem.eql(u8, dest[0..1], "\x00"));
    copyZ(dest[0..2], "hello");
    try expect(std.mem.eql(u8, dest[0..2], "h\x00"));
    copyZ(dest[0..3], "hello");
    try expect(std.mem.eql(u8, dest[0..3], "he\x00"));
    copyZ(dest[0..4], "hello");
    try expect(std.mem.eql(u8, dest[0..4], "hel\x00"));
    copyZ(dest[0..5], "hello");
    try expect(std.mem.eql(u8, dest[0..5], "hell\x00"));
    copyZ(dest[0..6], "hello");
    try expect(std.mem.eql(u8, dest[0..6], "hello\x00"));
    copyZ(dest[0..7], "hello");
    try expect(std.mem.eql(u8, dest[0..7], "hello\x00\xAE"));
}

//*****************************************************************************
// copy src slice to dst slice but make sure dst has a nil at end
pub fn utf8_to_utf8Z(allocator: *const std.mem.Allocator,
        u32_array: *std.ArrayListUnmanaged(u32), utf8: []u8,
        utf8_in: []const u8) !void
{
    try u32_array.resize(allocator.*, 0);
    try utf8_to_u32_array(allocator, utf8_in, u32_array);
    var bytes_written_out: usize = 0;
    try u32_array_to_utf8Z(u32_array, utf8, &bytes_written_out);
}

//*****************************************************************************
test "utf8_to_utf8Z"
{
    var u32_array = try std.ArrayListUnmanaged(u32).initCapacity(
            std.testing.allocator, 32);
    defer u32_array.deinit(std.testing.allocator);
    var dest: [10]u8 = .{0xAE} ** 10;
    const src = [_]u8{'j', 'a', 'y'};
    try utf8_to_utf8Z(&std.testing.allocator, &u32_array,
            dest[0..], src[0..]);
    try expect(std.mem.eql(u8, dest[0..4], "jay\x00"));
}

//*****************************************************************************
// copy src slice to dst slice but make sure dst has a nil at end
pub fn utf16_to_utf8Z(allocator: *const std.mem.Allocator,
        u32_array: *std.ArrayListUnmanaged(u32), utf8: []u8,
        utf16_in: []const u16) !void
{
    try u32_array.resize(allocator.*, 0);
    try utf16_to_u32_array(allocator, utf16_in, u32_array);
    var bytes_written_out: usize = 0;
    try u32_array_to_utf8Z(u32_array, utf8, &bytes_written_out);
}

//*****************************************************************************
test "utf16_to_utf8Z"
{
    var u32_array = try std.ArrayListUnmanaged(u32).initCapacity(
            std.testing.allocator, 32);
    defer u32_array.deinit(std.testing.allocator);
    var dest: [10]u8 = .{0xAE} ** 10;
    const src = [_]u16{'j', 'a', 'y'};
    try utf16_to_utf8Z(&std.testing.allocator, &u32_array,
            dest[0..], src[0..]);
    try expect(std.mem.eql(u8, dest[0..4], "jay\x00"));
}
