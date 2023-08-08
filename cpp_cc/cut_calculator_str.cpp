#include "cut_calculator.hpp"


#include <algorithm>
#include <numeric>
#include <string>
#include <cassert>
#include <cstdio>


using cc_bit = char;


using combo_bin = std::basic_string<cc_bit>;


namespace bin
{
	constexpr cc_bit CC_FALSE = '0';
	constexpr cc_bit CC_TRUE = '1';

	static bool has_bit(combo_bin const& bin)
	{
		// bin > 0;

		for (auto c : bin)
		{
			if (c == CC_TRUE)
			{
				return true;
			}
		}

		return false;
	}


	static bool has_common_bit(combo_bin const& bin1, combo_bin const& bin2)
	{
		// bin1 & bin2;

		auto const last = (int)bin1.length() - 1;

		for (int i = last; i >= 0; --i)
		{
			if (bin1[i] == CC_TRUE && bin2[i] == CC_TRUE)
			{
				return true;
			}
		}

		return false;
	}


	static void flip_bit(combo_bin& bin, u32 bit)
	{
		// bin = (1 << bit) ^ bin;

		bin[bit] = bin[bit] == CC_TRUE ? CC_FALSE : CC_TRUE;
	}


	static combo_bin zero(u32 len)
	{
		combo_bin bin(len, CC_FALSE);
		return bin;
	}


	static combo_bin one(u32 len)
	{
		combo_bin bin(len, CC_FALSE);
		bin.back() = CC_TRUE;

		return bin;
	}


	static void next_binary(combo_bin& bin)
	{
		// bin += 1;

		auto const last = (int)bin.length() - 1;

		for (int i = last; i >= 0; --i)
		{
			flip_bit(bin, i);
			if (bin[i] == CC_TRUE)
			{
				break;
			}
		}
	}


	static void skip_binary(combo_bin& bin)
	{
		// bin = (bin - 1) | bin + 1;

		auto const last = (int)bin.length() - 1;

		bin[last] = CC_TRUE;

		for (int i = last - 1; i >= 0 && bin[i] == CC_FALSE; --i)
		{
			bin[i] = CC_TRUE;
		}

		next_binary(bin);
	}


	static void combine_binary(combo_bin& bin, combo_bin const& other)
	{
		// bin = bin | other;

		auto const last = (int)bin.length() - 1;

		for (u32 i = 0; i < (u32)bin.length(); ++i)
		{
			if (other[i] == CC_TRUE || bin[i] == CC_TRUE)
			{
				bin[i] = CC_TRUE;
			}
		}
	}


	static void flip_all_bits(combo_bin& bin)
	{
		// bin = ~bin;

		for (auto& bit : bin)
		{
			bit = bit == CC_TRUE ? CC_FALSE : CC_TRUE;
		}
	}


	static combo_bin last(u32 len)
	{
		auto bin = zero(len);
		flip_all_bits(bin);

		return bin;
	}


	static bool test_has_bit()
	{
		bool result = true;

		combo_bin source[] = { "01110", "000", "1010110", "0000000", "0001000" };
		bool expected[]    = { true,    false, true,      false,     true };
		constexpr u32 N = 5;

		for (u32 i = 0; i < N; ++i)
		{
			auto& src = source[i];
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

		combo_bin source1[] = { "01110", "100", "1010110", "0001000", "0001000", "010101010101010101" };
		combo_bin source2[] = { "01010", "010", "0101010", "1111111", "0001000", "101010101010101010" };
		bool expected[]     = { true,    false, true,      true,      true,      false };
		constexpr u32 N = 6;

		for (u32 i = 0; i < N; ++i)
		{
			auto& src1 = source1[i];
			auto& src2 = source2[i];
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

		combo_bin source[]   = { "01110", "000", "101", "1010110", "0000000", "01011111", "1111111111" };
		combo_bin expected[] = { "01111", "001", "110", "1010111", "0000001", "01100000", "0000000000" };
		constexpr u32 N = 7;

		for (u32 i = 0; i < N; ++i)
		{
			auto& src = source[i];
			auto& exp = expected[i];
			next_binary(src);
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

		combo_bin source[]   = { "01110", "01111", "11001000", "1010110", "0000100", "01011111", "1111111111" };
		combo_bin expected[] = { "10000", "10000", "11010000", "1011000", "0001000", "01100000", "0000000000" };
		constexpr u32 N = 7;

		for (u32 i = 0; i < N; ++i)
		{
			auto& src = source[i];
			auto& exp = expected[i];
			skip_binary(src);
			result &= src == exp;
		}

		if (!result)
		{
			printf("test_skip_binary: FAIL\n");
		}

		return result;
	}


	static bool test_combine_binary()
	{
		bool result = true;

		combo_bin source1[]  = { "01110", "100", "1010110", "0001000", "0001000", "010101010101010101" };
		combo_bin source2[]  = { "01010", "010", "0101010", "1111111", "0001000", "101010101010101010" };
		combo_bin expected[] = { "01110", "110", "1111110", "1111111", "0001000", "111111111111111111" };
		constexpr u32 N = 6;

		for (u32 i = 0; i < N; ++i)
		{
			auto& src1 = source1[i];
			auto& src2 = source2[i];
			auto& exp = expected[i];
			combine_binary(src1, src2);
			result &= src1 == exp;
		}

		if (!result)
		{
			printf("test_combine_binary: FAIL\n");
		}

		return result;
	}


	static bool test_flip_all_bits()
	{
		bool result = true;

		combo_bin source[]   = { "01110", "000", "101", "1010110", "0100000", "01011111", "1111111111" };
		combo_bin expected[] = { "10001", "111", "010", "0101001", "1011111", "10100000", "0000000000" };
		constexpr u32 N = 7;

		for (u32 i = 0; i < N; ++i)
		{
			auto& src = source[i];
			auto& exp = expected[i];
			flip_all_bits(src);
			result &= src == exp;
		}

		if (!result)
		{
			printf("test_flip_all_bits: FAIL\n");
		}

		return result;
	}

}


namespace cut_calculator
{
	bool test_binary_ops()
	{
		bool result = true;

		result &= bin::test_has_bit();
		result &= bin::test_has_common_bit();
		result &= bin::test_next_binary();
		result &= bin::test_skip_binary();
		result &= bin::test_combine_binary();
		result &= bin::test_flip_all_bits();

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

			n_data_ids = (u32)data.size();
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


		void remove_at(u32 offset)
		{
			auto begin = sorted_data_ids.begin();
			auto end = begin + n_data_ids;
			auto data_id = id_at(offset);

			std::ignore = std::remove(begin, end, data_id);
			--n_data_ids;
		}


		f32 value_at(u32 offset) const
		{
			return data[id_at(offset)];
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
			std::sort(begin, end, [&](u64 a, u64 b) { return data[b] < data[a]; });
		}


		u32 id_at(u32 offset) const
		{
			return sorted_data_ids[offset];
		}


		f32 value_at(u32 offset) const
		{
			return data[id_at(offset)];
		}


		f32 combo_size(combo_bin const& bin) const
		{
			f32 size = 0.0f;

			for (u32 i = 0; i < bin.length(); ++i)
			{
				size += ((f32)(int)(bin[i] == bin::CC_TRUE)) * value_at(i);
			}

			return size;
		}


		std::vector<u32> combo_items(combo_bin const& bin)
		{
			std::vector<u32> item_ids;
			item_ids.reserve(bin.length());

			for (u32 i = 0; i < bin.length(); ++i)
			{
				if (bin[i] == bin::CC_TRUE)
				{
					item_ids.push_back(id_at(i));
				}
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


		void remove_combo_items(combo_bin const& bin)
		{
			auto last = (int)bin.length() - 1;

			for (int i = last; i >= 0; --i)
			{
				if (bin[i] == bin::CC_TRUE)
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

		combo_bin combo;
	};
}


static ComboCapacityMatch best_match(ItemSizeList const& sizes, ContainerCapacityList const& capacities)
{
	ComboCapacityMatch match{};

	f32 combo_size = 0.0f;
	auto max_capacity = capacities.max_value();
	auto best_diff = capacities.max_value();
	auto combo = bin::one(sizes.length());
	match.combo = combo;

	while (bin::has_bit(combo))
	{
		

		combo_size = sizes.combo_size(combo);
		if (combo_size > max_capacity)
		{
			bin::skip_binary(combo);
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
			std::copy(combo.begin(), combo.end(), match.combo.begin());
			match.capacity_offset = cap_offset;
		}

		bin::next_binary(combo);
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

		auto const n_items = item_list.length();
		auto const n_containers = container_list.length();

		//auto items_bin = bin::zero(n_items);
		auto last_bin = bin::last(n_items);

		SortResult result;

		while (item_list.length() && container_list.length())
		{
			auto match = best_match(item_list, container_list);

			auto capacity_id = container_list.id_at(match.capacity_offset);

			ContainerItems res{};
			res.container_id = capacity_id;
			res.container_capacity = container_capacities[capacity_id];
			res.item_ids = item_list.combo_items(match.combo);
			
			res.item_size = item_list.combo_size(match.combo);

			result.sorted.push_back(std::move(res));

			//bin::combine_binary(items_bin, match.combo);

			item_list.remove_combo_items(match.combo);
			container_list.remove_at(match.capacity_offset);
		}		

		//bin::flip_all_bits(items_bin);
		//result.unsorted_item_ids = item_list.combo_items(items_bin);

		for (u32 i = 0; i < item_list.length(); ++i)
		{
			result.unsorted_item_ids.push_back(item_list.id_at(i));
		}

		for (u32 i = 0; i < container_list.length(); ++i)
		{
			result.unsorted_container_ids.push_back(container_list.id_at(i));
		}

		return result;
	}
}
