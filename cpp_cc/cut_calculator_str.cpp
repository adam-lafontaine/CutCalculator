#include "cut_calculator.hpp"


#include <algorithm>
#include <numeric>
#include <string>
#include <cassert>
#include <cstdio>


using cc_bit = char;
constexpr cc_bit CC_FALSE = '0';
constexpr cc_bit CC_TRUE = '1';

using combo_bin = std::basic_string<cc_bit>;



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
	// bin_1 & bin_2;

	auto const last_1 = bin1.size() - 1;
	auto const last_2 = bin2.size() - 1;

	for (size_t i = 0; i <= last_1 && i <= last_2; ++i)
	{
		if (bin1[last_1 - i] == CC_TRUE && bin2[last_2 - i] == CC_TRUE)
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


static combo_bin zero_binary(u32 len)
{
	combo_bin bin(len, CC_FALSE);
	return bin;
}


static combo_bin first_binary(u32 len)
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


namespace cut_calculator
{
	bool test_binary_ops()
	{
		bool result = true;

		result &= test_has_bit();
		result &= test_has_common_bit();
		result &= test_next_binary();
		result &= test_skip_binary();
		result &= test_combine_binary();
		result &= test_flip_all_bits();

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
	class ComboSizePair
	{
	public:
		combo_bin bin;
		f32 size;
	};


	class ComboSizeList
	{
	private:
		std::vector<ComboSizePair> data;
		std::vector<u32> sorted_data_ids;

		u32 n_data_ids = 0;

	public:

		void add(combo_bin const& bin, f32 size)
		{
			sorted_data_ids.push_back((u32)data.size());
			data.push_back({ bin, size });
			++n_data_ids;
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


		void remove_common(combo_bin const& bin)
		{
			int last = (int)n_data_ids - 1;

			for (int i = last; i >= 0; --i)
			{
				auto offset = (u32)i;
				auto& combo = data[id_at(offset)].bin;

				if (has_common_bit(combo, bin))
				{
					remove_at(offset);
				}
			}
		}


		void remove_large(f32 max_capacity)
		{
			if (max_capacity <= 0.0f)
			{
				return;
			}

			int last = (int)n_data_ids - 1;

			for (int i = last; i >= 0; --i)
			{
				auto offset = (u32)i;
				auto size = data[id_at(offset)].size;

				if (size > max_capacity)
				{
					remove_at(offset);
				}
			}
		}


		f32 size_at(u32 offset) const { return data[id_at(offset)].size; }

		ComboSizePair data_at(u32 offset) const { return data[id_at(offset)]; }

		u32 length() const { return n_data_ids; }

		std::vector<ComboSizePair>& get_data() { return data; }
	};


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

	public:

		void set_data(std::vector<f32> const& sizes)
		{
			data = sizes;
			sorted_data_ids.resize(data.size());
			auto begin = sorted_data_ids.begin();
			auto end = sorted_data_ids.end();
			std::iota(begin, end, 0);
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
				if (bin[i] == CC_TRUE)
				{
					size += value_at(i);
				}
			}

			return size;
		}


		std::vector<u32> combo_items(combo_bin const& bin)
		{
			std::vector<u32> item_ids;
			item_ids.reserve(bin.length());

			for (u32 i = 0; i < bin.length(); ++i)
			{
				if (bin[i] == CC_TRUE)
				{
					item_ids.push_back(id_at(i));
				}
			}

			return item_ids;
		}


		u32 length() const { return (u32)sorted_data_ids.size(); }
	};


	class ComboCapacityMatch
	{
	public:
		u32 combo_offset = 0;
		u32 capacity_offset = 0;
	};
}


static ComboSizeList build_combos(ItemSizeList const& item_sizes, f32 max_capacity)
{
	ComboSizeList list;

	f32 combo_size = 0.0f;
	auto combo = first_binary(item_sizes.length());

	while (has_bit(combo))
	{
		combo_size = item_sizes.combo_size(combo);
		if (combo_size <= max_capacity)
		{
			list.add(combo, combo_size);
			next_binary(combo);
		}
		else
		{
			skip_binary(combo);
		}
	}

	return list;
}


static ComboCapacityMatch best_match(ComboSizeList const& combos, ContainerCapacityList const& capacities, f32 acc_diff = 0.0f)
{
	ComboCapacityMatch match{};

	auto best_diff = capacities.max_value();

	auto last = combos.length() - 1;

	for (int i = last; i >= 0; --i)
	{
		u32 combo_offset = (u32)i;
		auto size = combos.size_at(combo_offset);

		for (u32 cap_offset = 0; cap_offset < capacities.length(); ++cap_offset)
		{
			auto cap = capacities.value_at(cap_offset);
			auto diff = cap - size;

			if (diff < 0.0f || diff >= best_diff)
			{
				continue;
			}

			best_diff = diff;
			match.combo_offset = combo_offset;
			match.capacity_offset = cap_offset;			

			if (diff <= acc_diff)
			{
				return match;
			}
		}
	}

	return match;
}


static void print_combos(ComboSizeList const& combos)
{
	auto last = combos.length() - 1;
	auto first = last > 9 ? last - 9 : 0;

	for (int i = last; i >= first; --i)
	{
		auto combo = combos.data_at(i);
		printf("%s, %f\n", combo.bin.c_str(), combo.size);
	}
}



namespace cut_calculator
{
	SortResult sort(std::vector<f32> const& item_sizes, std::vector<f32> const& container_capacities, f32 acc_diff)
	{
		ItemSizeList item_list;
		ContainerCapacityList container_list;

		item_list.set_data(item_sizes);
		item_list.sort();

		container_list.set_data(container_capacities);
		container_list.sort();

		auto combo_list = build_combos(item_list, container_list.max_value());
		print_combos(combo_list);

		auto const n_items = item_list.length();
		auto const n_containers = container_list.length();

		std::vector<int> container_combos(n_containers, -1);

		auto& combo_sizes = combo_list.get_data();

		auto items_bin = zero_binary(n_items);

		while (combo_list.length() && container_list.length())
		{
			auto match = best_match(combo_list, container_list, acc_diff);

			auto capacity_id = container_list.id_at(match.capacity_offset);
			auto combo_id = combo_list.id_at(match.combo_offset);

			printf("%u/%u/%u\n", combo_list.length(), capacity_id, combo_id);

			container_combos[capacity_id] = combo_id;

			auto& item_combo = combo_sizes[combo_id].bin;
			combine_binary(items_bin, item_combo);

			container_list.remove_at(match.capacity_offset);
			combo_list.remove_common(item_combo);
			combo_list.remove_large(container_list.max_value());
		}
		
		SortResult result;

		flip_all_bits(items_bin);
		result.unsorted_item_ids = item_list.combo_items(items_bin);

		for (int cap_id = 0; cap_id < container_combos.size(); ++cap_id)
		{
			auto combo_id = container_combos[cap_id];
			if (combo_id < 0)
			{
				result.unsorted_container_ids.push_back(cap_id);
				continue;
			}

			auto& combo = combo_sizes[combo_id];

			ContainerItems res{};
			res.container_id = cap_id;
			res.container_capacity = container_capacities[cap_id];
			res.item_ids = item_list.combo_items(combo.bin);
			res.item_size = combo.size;

			result.sorted.push_back(std::move(res));
		}

		return result;
	}
}
