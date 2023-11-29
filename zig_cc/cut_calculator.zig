const std = @import("std");
const testing = std.testing;
const assert = std.debug.assert;

const combo_bin = u128;

const Bin = struct
{

const zero: combo_bin = 0;
const one: combo_bin = 1;

fn combo_mask(len: anytype) combo_bin 
{    
    assert(len <= 128);
    return (one << @truncate(len)) - one;
}

fn has_bit(bin: combo_bin) bool 
{
    return bin > 0;
}

fn has_common_bit(bin1: combo_bin, bin2: combo_bin) bool 
{
    return bin1 & bin2 > 0;
}

fn next_binary(bin_ref: *combo_bin, mask: combo_bin) void 
{
    const bin = bin_ref.*;
    bin_ref.* = (bin + one) & mask;
}

fn skip_binary(bin_ref: *combo_bin, mask: combo_bin) void 
{
    const bin = bin_ref.*;
    bin_ref.* = (((bin - one) | bin) + one) & mask;
}

fn flip_all_bits(bin_ref: *combo_bin, mask: combo_bin) void 
{
    const bin = bin_ref.*;
    bin_ref.* = (~bin) & mask;
}

fn combine_binary(bin_ref: *combo_bin, other: combo_bin) void 
{
    bin_ref.* |= other;
}

};



test "combo_mask" 
{
    var result: bool = true;

    const source = [_]u32{ 2, 3, 4, 5, 6, 16 };
    const expected = [_]combo_bin{ 0b11, 0b111, 0b1111, 0b11111, 0b111111, 0b1111111111111111 };

    for (source, expected) |src, exp|
    {
        result = result and (Bin.combo_mask(src) == exp);
    }

    try testing.expect(result);
}


test "has_bit"
{
    var result: bool = true;

    const source  =  [_]combo_bin{ 0b01110, 0b000, 0b1010110, 0b0000000, 0b0001000 };
    const expected = [_]bool{      true,    false, true,      false,     true };

    for (source, expected) |src, exp|
    {
        result = result and (Bin.has_bit(src) == exp);
    }

    try testing.expect(result);
}


test "has_common_bit"
{
    var result: bool = true;

    const source1  = [_]combo_bin{ 0b01110, 0b100, 0b1010110, 0b0001000, 0b0001000, 0b010101010101010101 };
    const source2  = [_]combo_bin{ 0b01010, 0b010, 0b0101010, 0b1111111, 0b0001000, 0b101010101010101010 };
    const expected =      [_]bool{ true,    false, true,      true,      true,      false };

    for (source1, source2, expected) |src1, src2, exp|
    {
        result = result and (Bin.has_common_bit(src1, src2) == exp);
    }

    try testing.expect(result);
}


test "next_binary"
{
    var result: bool = true;

    var source =     [_]combo_bin{ 0b01110, 0b000, 0b101, 0b1010110, 0b0000000, 0b01011111, 0b1111111111 };
    const expected = [_]combo_bin{ 0b01111, 0b001, 0b110, 0b1010111, 0b0000001, 0b01100000, 0b0000000000 };
    const masks =    [_]combo_bin{ 0b11111, 0b111, 0b111, 0b1111111, 0b1111111, 0b11111111, 0b1111111111 };

    for (&source, expected, masks) |*src, exp, mask|
    {
        Bin.next_binary(src, mask);
        result = result and (src.* == exp);
    }

    try testing.expect(result);
}


test "skip_binary"
{
    var result: bool = true;

    var source =     [_]combo_bin{ 0b01110, 0b01111, 0b11001000, 0b1010110, 0b0000100, 0b01011111, 0b1111111111 };
    const expected = [_]combo_bin{ 0b10000, 0b10000, 0b11010000, 0b1011000, 0b0001000, 0b01100000, 0b0000000000 };
    const masks =    [_]combo_bin{ 0b11111, 0b11111, 0b11111111, 0b1111111, 0b1111111, 0b11111111, 0b1111111111 };

    for (&source, expected, masks) |*src, exp, mask|
    {
        Bin.skip_binary(src, mask);
        result = result and (src.* == exp);
    }

    try testing.expect(result);
}


test "flip_all_bits"
{
    var result: bool = true;

    var source =     [_]combo_bin{ 0b01110, 0b000, 0b101, 0b1010110, 0b0100000, 0b01011111, 0b1111111111 };
    const expected = [_]combo_bin{ 0b10001, 0b111, 0b010, 0b0101001, 0b1011111, 0b10100000, 0b0000000000 };
    const masks =    [_]combo_bin{ 0b11111, 0b111, 0b111, 0b1111111, 0b1111111, 0b11111111, 0b1111111111 };

    for (&source, expected, masks) |*src, exp, mask|
    {
        Bin.flip_all_bits(src, mask);
        result = result and (src.* == exp);
    }

    try testing.expect(result);
}


test "combine_binary"
{
    var result: bool = true;

    var source1  =   [_]combo_bin{ 0b01110, 0b100, 0b1010110, 0b0001000, 0b0001000, 0b010101010101010101 };
    const source2  = [_]combo_bin{ 0b01010, 0b010, 0b0101010, 0b1111111, 0b0001000, 0b101010101010101010 };
    const expected = [_]combo_bin{ 0b01110, 0b110, 0b1111110, 0b1111111, 0b0001000, 0b111111111111111111 };

    for (&source1, source2, expected) |*src1, src2, exp|
    {
        Bin.combine_binary(src1, src2);
        result = result and (src1.* == exp);
    }

    try testing.expect(result);
}