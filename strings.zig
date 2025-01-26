const std = @import("std");

//*********************************************************************************
pub fn utf8_to_u32_array(utf8_in: []const u8, utf32_out: *std.ArrayList(u32)) !void
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
            2 => try std.unicode.utf8Decode2(utf8_in[in_start..in_end]),
            3 => try std.unicode.utf8Decode3(utf8_in[in_start..in_end]),
            4 => try std.unicode.utf8Decode4(utf8_in[in_start..in_end]),
            else => return error.Unexpected,
        };
        in_index += in_bytes;
        try utf32_out.append(chr21);
    }
    // remove any trailing zeros
    while ((utf32_out.items.len > 0) and
            (utf32_out.items[utf32_out.items.len - 1] == 0))
    {
        utf32_out.items.len -= 1;
    }
}

//*********************************************************************************
pub fn utf16_to_u32_array(utf16_in: []const u16, utf32_out: *std.ArrayList(u32)) !void
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
        try utf32_out.append(chr21);
    }
    // remove any trailing zeros
    while ((utf32_out.items.len > 0) and
            (utf32_out.items[utf32_out.items.len - 1] == 0))
    {
        utf32_out.items.len -= 1;
    }
}

//*********************************************************************************
pub fn u32_array_to_utf16Z_as_u8(u32_array: *std.ArrayList(u32),
        utf16_as_u8: []u8, bytes_written_out: *usize) !void
{
    if ((utf16_as_u8.len >> 1) < 1)
    {
        return error.Unexpected;
    }
    @memset(utf16_as_u8, 0);
    bytes_written_out.* = 0;
    var chr21: u21 = undefined;
    var out_index: usize = 0;
    const out_max = (utf16_as_u8.len >> 1) - 1;
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
            bytes_written_out.* += 2;
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
            bytes_written_out.* += 4;
        }
    }
}

//*********************************************************************************
pub fn utf8_to_utf16Z_as_u8(u32_array: *std.ArrayList(u32),
        utf8: []const u8, utf16_as_u8: []u8, cbSize: *u16) !void
{
    try u32_array.resize(0);
    try utf8_to_u32_array(utf8, u32_array);
    var bytes_written_out: usize = 0;
    if (u32_array_to_utf16Z_as_u8(u32_array, utf16_as_u8,
            &bytes_written_out)) |_| { } else |err|
    {
        if (err != error.NoRoom)
        {
            return err;
        }
    }
    cbSize.* = @truncate(bytes_written_out);
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
