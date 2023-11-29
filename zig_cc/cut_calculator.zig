const std = @import("std");
const testing = std.testing;

const combo_bin = u128;

const zero: combo_bin = 0;
const one: combo_bin = 1;

fn combo_mask(len: u32) combo_bin {
    return (one << len) - one;
}

fn has_bit(bin: combo_bin) bool {
    return bin > 0;
}

fn has_common_bit(bin1: combo_bin, bin2: combo_bin) bool {
    return bin1 & bin2;
}

fn next_binary(bin_ref: *combo_bin, mask: combo_bin) void {
    const bin = bin_ref.*;
    bin_ref.* = (bin + one) & mask;
}

fn skip_binary(bin_ref: *combo_bin, mask: combo_bin) void {
    const bin = bin_ref.*;
    bin_ref.* = (((bin - one) | bin) + one) & mask;
}

fn flip_all_bits(bin_ref: *combo_bin, mask: combo_bin) void {
    const bin = bin_ref.*;
    bin_ref.* = (~bin) & mask;
}

fn combine_binary(bin_ref: *combo_bin, other: combo_bin) void {
    bin_ref.* = bin_ref.* | other;
}

test "combo_mask" {
    var result: bool = true;

    try testing.expect(result);
}
