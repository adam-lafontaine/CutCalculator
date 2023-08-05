#include "cut_calculator.hpp"

#include <algorithm>
#include <numeric>
#include <cassert>
#include <cstdio>


using combo_bin = u64;

constexpr combo_bin zero_binary = 0;

constexpr u64 mask = ((u64)1 << 4) - 1;

constexpr u64 last = (u64)0 - 1;


static inline combo_bin combo_mask(u32 len)
{
	return ((combo_bin)1 << len) - (combo_bin)1;
}


static inline bool has_bit(combo_bin bin)
{
	return bin > 0;
}


static inline bool has_common_bit(combo_bin bin1, combo_bin bin2)
{
	return bin1 & bin2;
}


static inline void next_binary(combo_bin& bin, combo_bin mask)
{
	bin = (bin + 1) & mask;
}


static inline void skip_binary(combo_bin& bin, combo_bin mask)
{
	bin = (((bin - 1) | bin) + 1) & mask;
}


static inline void flip_all_bits(combo_bin& bin, combo_bin mask)
{
	bin = (~bin) & mask;
}


static void combine_binary(combo_bin& bin, combo_bin other)
{
	bin = bin | other;
}


static bool test_combo_mask()
{
	bool result = true;

	u32 source[]   = { 2, 3, 4, 5, 6, 16 };
	u64 expected[] = { 0b11, 0b111, 0b1111, 0b11111, 0b111111, 0b1111111111111111 };
	constexpr u32 N = 6;

	for (u32 i = 0; i < N; ++i)
	{
		auto src = source[i];
		auto exp = expected[i];
		result &= combo_mask(src) == exp;
	}

	if (!result)
	{
		printf("test_combo_mask: FAIL\n");
	}

	return result;
}


static bool test_has_bit()
{
	bool result = true;

	combo_bin source[] = { 0b01110, 0b000, 0b1010110, 0b0000000, 0b0001000 };
	bool expected[]    = { true,    false, true,      false,     true };
	constexpr u32 N = 5;

	for (u32 i = 0; i < N; ++i)
	{
		auto src = source[i];
		auto exp = expected[i];
		result &= has_bit(src) == exp;
	}

	if (!result)
	{
		printf("test_has_bit: FAIL\n");
	}

	return result;
}


static bool test_has_common_bit()
{
	bool result = true;

	combo_bin source1[] = { 0b01110, 0b100, 0b1010110, 0b0001000, 0b0001000, 0b010101010101010101 };
	combo_bin source2[] = { 0b01010, 0b010, 0b0101010, 0b1111111, 0b0001000, 0b101010101010101010 };
	bool expected[]     = { true,    false, true,      true,      true,      false };
	constexpr u32 N = 6;

	for (u32 i = 0; i < N; ++i)
	{
		auto src1 = source1[i];
		auto src2 = source2[i];
		auto exp = expected[i];
		result &= has_common_bit(src1, src2) == exp;
	}

	if (!result)
	{
		printf("test_has_common_bit: FAIL\n");
	}

	return result;
}


static bool test_next_binary()
{
	bool result = true;

	combo_bin source[]   = { 0b01110, 0b000, 0b101, 0b1010110, 0b0000000, 0b01011111, 0b1111111111 };
	combo_bin expected[] = { 0b01111, 0b001, 0b110, 0b1010111, 0b0000001, 0b01100000, 0b0000000000 };
	combo_bin masks[]    = { 0b11111, 0b111, 0b111, 0b1111111, 0b1111111, 0b11111111, 0b1111111111 };
	constexpr u32 N = 7;

	for (u32 i = 0; i < N; ++i)
	{
		auto src = source[i];
		auto exp = expected[i];
		auto mask = masks[i];
		next_binary(src, mask);
		result &= src == exp;
	}

	if (!result)
	{
		printf("test_next_binary: FAIL\n");
	}

	return result;
}


static bool test_skip_binary()
{
	bool result = true;

	combo_bin source[]   = { 0b01110, 0b01111, 0b11001000, 0b1010110, 0b0000100, 0b01011111, 0b1111111111 };
	combo_bin expected[] = { 0b10000, 0b10000, 0b11010000, 0b1011000, 0b0001000, 0b01100000, 0b0000000000 };
	combo_bin masks[]    = { 0b11111, 0b11111, 0b11111111, 0b1111111, 0b1111111, 0b11111111, 0b1111111111 };
	constexpr u32 N = 7;

	for (u32 i = 0; i < N; ++i)
	{
		auto src = source[i];
		auto exp = expected[i];
		auto mask = masks[i];
		skip_binary(src, mask);
		result &= src == exp;
	}

	if (!result)
	{
		printf("test_skip_binary: FAIL\n");
	}

	return result;
}


static bool test_flip_all_bits()
{
	bool result = true;

	combo_bin source[]   = { 0b01110, 0b000, 0b101, 0b1010110, 0b0100000, 0b01011111, 0b1111111111 };
	combo_bin expected[] = { 0b10001, 0b111, 0b010, 0b0101001, 0b1011111, 0b10100000, 0b0000000000 };
	combo_bin masks[]    = { 0b11111, 0b111, 0b111, 0b1111111, 0b1111111, 0b11111111, 0b1111111111 };
	constexpr u32 N = 7;

	for (u32 i = 0; i < N; ++i)
	{
		auto src = source[i];
		auto exp = expected[i];
		auto mask = masks[i];
		flip_all_bits(src, mask);
		result &= src == exp;
	}

	if (!result)
	{
		printf("test_flip_all_bits: FAIL\n");
	}

	return result;
}


static bool test_combine_binary()
{
	bool result = true;

	combo_bin source1[]  = { 0b01110, 0b100, 0b1010110, 0b0001000, 0b0001000, 0b010101010101010101 };
	combo_bin source2[]  = { 0b01010, 0b010, 0b0101010, 0b1111111, 0b0001000, 0b101010101010101010 };
	combo_bin expected[] = { 0b01110, 0b110, 0b1111110, 0b1111111, 0b0001000, 0b111111111111111111 };
	constexpr u32 N = 6;

	for (u32 i = 0; i < N; ++i)
	{
		auto src1 = source1[i];
		auto src2 = source2[i];
		auto exp = expected[i];
		combine_binary(src1, src2);
		result &= src1 == exp;
	}

	if (!result)
	{
		printf("test_combine_binary: FAIL\n");
	}

	return result;
}


namespace cut_calculator
{
	bool test_binary_ops()
	{
		bool result = true;

		result &= test_combo_mask();
		result &= test_has_bit();
		result &= test_has_common_bit();
		result &= test_next_binary();
		result &= test_skip_binary();
		result &= test_flip_all_bits();
		result &= test_combine_binary();		

		if (result)
		{
			printf("test_binary_ops: OK\n");
		}

		return result;
	}
}