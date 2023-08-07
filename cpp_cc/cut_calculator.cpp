#include "cut_calculator.hpp"

#include <algorithm>
#include <numeric>
#include <cassert>
//#include <cstdio>


using combo_bin = u64;

constexpr combo_bin binary_zero = 0;
constexpr combo_bin binary_one = 0;

constexpr u64 binary_last = binary_zero - 1;

constexpr u64 mask = ((u64)1 << 4) - 1;


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

		void add(combo_bin bin, f32 size)
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
				auto size = size_at(offset);

				if (size > max_capacity)
				{
					remove_at(offset);
				}
			}
		}


		f32 size_at(u32 offset) const { return data[id_at(offset)].size; }

		combo_bin combo_at(u32 offset) const { return data[id_at(offset)].bin; }

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


		f32 combo_size(combo_bin bin) const
		{
			f32 size = 0.0f;
			auto len = (u32)data.size();

			u64 p = 1;
			for (u32 i = 0; i < len; ++i, p *= 2)
			{
				if (p & bin)
				{
					size += value_at(i);
				}
			}

			return size;
		}


		std::vector<u32> combo_items(combo_bin bin)
		{
			std::vector<u32> item_ids;
			item_ids.reserve(data.size());

			auto len = (u32)data.size();

			u64 p = 1;
			for (u32 i = 0; i < len; ++i, p *= 2)
			{
				if (p & bin)
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
	auto combo = binary_one;
	auto mask = combo_mask(item_sizes.length());

	while (has_bit(combo))
	{
		combo_size = item_sizes.combo_size(combo);
		if (combo_size <= max_capacity)
		{
			list.add(combo, combo_size);
			next_binary(combo, mask);
		}
		else
		{
			skip_binary(combo, mask);
		}
	}

	return list;
}


static ComboCapacityMatch best_match(ComboSizeList const& combos, combo_bin excluded_items, ContainerCapacityList const& capacities, f32 acc_diff = 0.0f)
{
	ComboCapacityMatch match{};

	auto best_diff = capacities.max_value();

	auto last = combos.length() - 1;

	for (int i = last; i >= 0; --i)
	{
		u32 combo_offset = (u32)i;
		auto combo = combos.combo_at(combo_offset);

		if (has_common_bit(combo, excluded_items))
		{
			continue;
		}

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


//static void print_binary(combo_bin bin, u32 len)
//{
//	u64 p = 1 << (len - 1);
//	for (u32 i = 0; i < len; ++i, p = p >> 1)
//	{
//		if (p & bin)
//		{
//			printf("1");
//		}
//		else
//		{
//			printf("0");
//		}
//	}
//}
//
//
//static void print_combos(ComboSizeList const& combos, u32 len)
//{
//	auto last = combos.length() - 1;
//	auto first = last > 9 ? last - 9 : 0;
//
//	for (int i = last; i >= first; --i)
//	{
//		auto combo = combos.data_at(i);
//		print_binary(combo.bin, len);
//		printf(", %f\n", combo.size);
//	}
//}


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

		auto const n_items = item_list.length();
		auto const n_containers = container_list.length();

		std::vector<int> container_combos(n_containers, -1);

		auto& combo_sizes = combo_list.get_data();		

		auto items_bin = binary_zero;
		auto items_mask = combo_mask(n_items);

		while (combo_list.length() && container_list.length())
		{
			auto match = best_match(combo_list, items_bin, container_list, acc_diff);

			auto capacity_id = container_list.id_at(match.capacity_offset);
			auto combo_id = combo_list.id_at(match.combo_offset);

			container_combos[capacity_id] = combo_id;

			auto& item_combo = combo_sizes[combo_id].bin;
			combine_binary(items_bin, item_combo);

			container_list.remove_at(match.capacity_offset);
			combo_list.remove_large(container_list.max_value());
		}

		SortResult result;

		flip_all_bits(items_bin, items_mask);
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