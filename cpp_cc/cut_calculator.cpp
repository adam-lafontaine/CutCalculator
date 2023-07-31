#include <cstdint>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using i8 = int8_t;
using i16 = short;
using i32 = int32_t;
using cstr = const char*;
using b32 = u32;


#include <algorithm>
#include <vector>
#include <map>
#include <string>


using cc_bit = char;
constexpr cc_bit CC_FALSE = '0';
constexpr cc_bit CC_TRUE = '1';

using combo_key = std::basic_string<cc_bit>;



using ComboList = std::vector<combo_key>;
using SizeList = std::vector<f32>;


class ComboSizeMap
{
private:
	ComboList keys_;
	SizeList sizes_;

public:

	void add(combo_key const& key, f32 size) 
	{
		keys_.push_back(key);
		sizes_.push_back(size);
	}


	void remove_at(u32 id)
	{
		keys_.erase(keys_.begin() + id);
		sizes_.erase(sizes_.begin() + id);
	}


	combo_key combo_at(u32 id) { return keys_[id]; }

	f32 size_at(u32 id) { return sizes_[id]; }

	u64 length() { return keys_.size(); }
};


static bool has_bit(combo_key const& bin)
{
	for (auto c : bin)
	{
		if (c == CC_TRUE)
		{
			return true;
		}
	}

	return false;
}


static bool has_common_bit(combo_key const& bin_1, combo_key const& bin_2)
{
	// AND operation

	auto const last_1 = bin_1.size() - 1;
	auto const last_2 = bin_2.size() - 1;

	for (size_t i = 0; i <= last_1 && i <= last_2; ++i) 
	{
		if (bin_1[last_1 - i] == CC_TRUE && bin_2[last_2 - i] == CC_TRUE)
		{
			return true;
		}			
	}

	return false;
}


static void flip_bit(combo_key& bin, u32 bit)
{
	bin[bit] = bin[bit] == CC_TRUE ? CC_FALSE : CC_TRUE;
}


static void next_binary(combo_key& bin)
{
	// Add one

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


static void skip_binary(combo_key& bin)
{
	auto const last = (int)bin.length() - 1;

	bin[last] = CC_TRUE;

	for (int i = last - 1; i >= 0 && bin[i] == CC_FALSE; --i)
	{
		bin[i] = CC_TRUE;
	}

	next_binary(bin);
}









constexpr u32 MAX_ITEMS = sizeof(u64) * 8;

u32 n_items = 0;
u32 n_cap = 0;


f32 item_sizes[MAX_ITEMS] = { 0 };

f32 capacities[MAX_ITEMS] = { 0 };


u32 item_ids[MAX_ITEMS] = { 0 };

u32 cap_ids[MAX_ITEMS] = { 0 };





static bool cap_asc(u32 cap_id_lhs, u32 cap_id_rhs)
{
	return capacities[cap_id_lhs] < capacities[cap_id_rhs];
}


static bool item_desc(u32 item_id_lhs, u32 item_id_rhs)
{
	return item_sizes[item_id_rhs] < item_sizes[item_id_lhs];
}


static void reset_ids()
{
	for (u32 i = 0; i < MAX_ITEMS; ++i)
	{
		item_ids[i] = cap_ids[i] = i;
	}

	auto begin = item_ids;
	auto end = begin + n_items;
	std::sort(begin, end, item_desc);

	begin = cap_ids;
	end = begin + n_cap;
	std::sort(begin, end, cap_asc);
}


static f32 item_combo_size(u64 item_combo)
{
	f32 size = 0.0f;

	u64 p = 1;
	for (u32 i = 0; i < n_items; ++i, p *= 2)
	{
		if (p & item_combo)
		{
			size += item_sizes[i];
		}
	}

	return size;
}


static ComboSizeMap build_map()
{
	ComboSizeMap map;

	f32 max_capacity = capacities[cap_ids[n_cap - 1]];
	f32 combo_size = 0.0f;
	u64 combo = 1;

	while (combo)
	{
		combo_size = item_combo_size(combo);
		if (combo_size <= max_capacity)
		{

		}
		else
		{
			
		}
	}


	return map;
}



void sort()
{
	reset_ids();
}
