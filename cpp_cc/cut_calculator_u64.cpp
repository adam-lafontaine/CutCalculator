#include "cut_calculator.hpp"

#include <algorithm>
#include <numeric>
#include <cassert>


using combo_bin = u64;


namespace bin
{
	constexpr combo_bin zero = 0;
	constexpr combo_bin one = 1;


	static inline combo_bin combo_mask(u32 len)
	{
		return (one << len) - one;
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
		bin = (bin + one) & mask;
	}


	static inline void skip_binary(combo_bin& bin, combo_bin mask)
	{
		bin = (((bin - one) | bin) + one) & mask;
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

		u32 source[] = { 2, 3, 4, 5, 6, 16 };
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
		bool expected[] = { true,    false, true,      false,     true };
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
		bool expected[] = { true,    false, true,      true,      true,      false };
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

		combo_bin source[] = { 0b01110, 0b000, 0b101, 0b1010110, 0b0000000, 0b01011111, 0b1111111111 };
		combo_bin expected[] = { 0b01111, 0b001, 0b110, 0b1010111, 0b0000001, 0b01100000, 0b0000000000 };
		combo_bin masks[] = { 0b11111, 0b111, 0b111, 0b1111111, 0b1111111, 0b11111111, 0b1111111111 };
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

		combo_bin source[] = { 0b01110, 0b01111, 0b11001000, 0b1010110, 0b0000100, 0b01011111, 0b1111111111 };
		combo_bin expected[] = { 0b10000, 0b10000, 0b11010000, 0b1011000, 0b0001000, 0b01100000, 0b0000000000 };
		combo_bin masks[] = { 0b11111, 0b11111, 0b11111111, 0b1111111, 0b1111111, 0b11111111, 0b1111111111 };
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

		combo_bin source[] = { 0b01110, 0b000, 0b101, 0b1010110, 0b0100000, 0b01011111, 0b1111111111 };
		combo_bin expected[] = { 0b10001, 0b111, 0b010, 0b0101001, 0b1011111, 0b10100000, 0b0000000000 };
		combo_bin masks[] = { 0b11111, 0b111, 0b111, 0b1111111, 0b1111111, 0b11111111, 0b1111111111 };
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

		combo_bin source1[] = { 0b01110, 0b100, 0b1010110, 0b0001000, 0b0001000, 0b010101010101010101 };
		combo_bin source2[] = { 0b01010, 0b010, 0b0101010, 0b1111111, 0b0001000, 0b101010101010101010 };
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
}


namespace cut_calculator
{
	bool test_binary_ops()
	{
		bool result = true;

		result &= bin::test_combo_mask();
		result &= bin::test_has_bit();
		result &= bin::test_has_common_bit();
		result &= bin::test_next_binary();
		result &= bin::test_skip_binary();
		result &= bin::test_flip_all_bits();
		result &= bin::test_combine_binary();

		if (result)
		{
			printf("test_binary_ops: OK\n");
		}

		return result;
	}
}


/* classes */

namespace
{
	class ContainerCapacityList
	{
	private:
		std::vector<f32> data;
		std::vector<u32> sorted_data_ids;

		u32 n_data_ids = 0;

	public:

		void set_data(std::vector<f32> const& capacities)
		{
			data = capacities;
			sorted_data_ids.resize(data.size());
			auto begin = sorted_data_ids.begin();
			auto end = sorted_data_ids.end();
			std::iota(begin, end, 0);

			n_data_ids = (u32)capacities.size();
		}


		void sort()
		{
			auto begin = sorted_data_ids.begin();
			auto end = sorted_data_ids.end();
			std::sort(begin, end, [&](u64 a, u64 b) { return data[a] < data[b]; });
		}


		u32 id_at(u32 offset) const
		{
			return sorted_data_ids[offset];
		}


		f32 value_at(u32 offset) const
		{
			return data[id_at(offset)];
		}
		
		
		std::vector<u32> ids()
		{
			auto len = length();

			std::vector<u32> item_ids;
			item_ids.reserve(len);

			for (u32 i = 0; i < len; ++i)
			{
				item_ids.push_back(id_at(i));
			}

			return item_ids;
		}


		void remove_at(u32 offset)
		{
			auto begin = sorted_data_ids.begin();
			auto end = begin + n_data_ids;
			auto data_id = id_at(offset);

			std::ignore = std::remove(begin, end, data_id);
			--n_data_ids;
		}


		f32 max_value() const { return data[sorted_data_ids.back()]; }

		u32 length() const { return n_data_ids; }
	};


	class ItemSizeList
	{
	private:
		std::vector<f32> data;
		std::vector<u32> sorted_data_ids;

		u32 n_data_ids = 0;

	public:

		void set_data(std::vector<f32> const& sizes)
		{
			data = sizes;
			sorted_data_ids.resize(data.size());
			auto begin = sorted_data_ids.begin();
			auto end = sorted_data_ids.end();
			std::iota(begin, end, 0);

			n_data_ids = (u32)data.size();
		}


		void sort()
		{
			auto begin = sorted_data_ids.begin();
			auto end = sorted_data_ids.end();
			std::sort(begin, end, [&](u64 a, u64 b) { return data[b] > data[a]; });
		}


		u32 id_at(u32 offset) const
		{
			return sorted_data_ids[offset];
		}


		f32 value_at(u32 offset) const
		{
			return data[id_at(offset)];
		}


		std::vector<u32> ids()
		{
			auto len = length();

			std::vector<u32> item_ids;
			item_ids.reserve(len);

			for (u32 i = 0; i < len; ++i)
			{
				item_ids.push_back(id_at(i));
			}

			return item_ids;
		}


		std::vector<u32> combo_ids(combo_bin bin)
		{
			auto len = length();

			std::vector<u32> item_ids;
			item_ids.reserve(len);

			u64 p = 1;
			for (u32 i = 0; i < len; ++i, p = p << (u64)1)
			{
				if (p & bin)
				{
					item_ids.push_back(id_at(i));
				}
			}

			return item_ids;
		}


		f32 combo_size(combo_bin bin) const
		{
			f32 size = 0.0f;
			auto len = (u32)data.size();

			u64 p = 1;
			for (u32 i = 0; i < len; ++i, p = p << (u64)1)
			{
				size += ((f32)(int)(bool)(p & bin)) * value_at(i);
			}

			return size;
		}


		void remove_at(u32 offset)
		{
			auto begin = sorted_data_ids.begin();
			auto end = begin + n_data_ids;
			auto data_id = id_at(offset);

			std::ignore = std::remove(begin, end, data_id);
			--n_data_ids;
		}


		void remove_combo_items(combo_bin bin)
		{
			auto len = length();
			auto last = len - 1;

			u64 p = (u64)1 << (len - 1);

			for (int i = last; i >= 0; --i, p = p >> (u64)1)
			{
				if (p & bin)
				{
					remove_at(i);
				}
			}
		}


		u32 length() const { return n_data_ids; }
	};


	class ComboCapacityMatch
	{
	public:
		u32 capacity_offset = 0;
		combo_bin combo = bin::zero;

		bool success = false;
	};
}


static ComboCapacityMatch best_match(ItemSizeList const& sizes, ContainerCapacityList const& capacities)
{
	ComboCapacityMatch match{};
	match.success = false;

	f32 combo_size = 0.0f;
	auto max_capacity = capacities.max_value();
	auto best_diff = capacities.max_value();
	auto combo = bin::one;
	auto mask = bin::combo_mask(sizes.length());

	while (bin::has_bit(combo))
	{
		combo_size = sizes.combo_size(combo);
		if (combo_size > max_capacity)
		{
			bin::skip_binary(combo, mask);
			continue;			
		}

		for (u32 cap_offset = 0; cap_offset < capacities.length(); ++cap_offset)
		{
			auto cap = capacities.value_at(cap_offset);
			auto diff = cap - combo_size;

			if (diff < 0.0f || diff > best_diff)
			{
				continue;
			}

			best_diff = diff;
			match.combo = combo;
			match.capacity_offset = cap_offset;
			match.success = true;
		}

		bin::next_binary(combo, mask);
	}

	return match;
}


namespace cut_calculator
{
	SortResult sort(std::vector<f32> const& item_sizes, std::vector<f32> const& container_capacities)
	{
		ItemSizeList item_list;
		ContainerCapacityList container_list;

		item_list.set_data(item_sizes);
		item_list.sort();

		container_list.set_data(container_capacities);
		container_list.sort();

		SortResult result;

		while (item_list.length() && container_list.length())
		{
			auto match = best_match(item_list, container_list);
			if (!match.success)
			{
				break;
			}

			auto capacity_id = container_list.id_at(match.capacity_offset);

			ContainerItems res{};
			res.container_id = capacity_id;
			res.container_capacity = container_capacities[capacity_id];
			res.item_ids = item_list.combo_ids(match.combo);			
			res.item_size = item_list.combo_size(match.combo);

			result.sorted.push_back(std::move(res));

			item_list.remove_combo_items(match.combo);
			container_list.remove_at(match.capacity_offset);
		}

		result.unsorted_item_ids = item_list.ids();
		result.unsorted_container_ids = container_list.ids();

		return result;
	}
}