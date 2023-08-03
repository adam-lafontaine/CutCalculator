#include "cut_calculator.hpp"


#include <algorithm>
#include <numeric>
#include <string>
#include <cassert>


using cc_bit = char;
constexpr cc_bit CC_FALSE = '0';
constexpr cc_bit CC_TRUE = '1';

using combo_key = std::basic_string<cc_bit>;



static bool has_common_bit(combo_key const& bin_1, combo_key const& bin_2)
{
	// bin_1 & bin_2;

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


static bool has_bit(combo_key const& bin)
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


static void flip_bit(combo_key& bin, u32 bit)
{
	// bin = (1 << bit) ^ bin;

	bin[bit] = bin[bit] == CC_TRUE ? CC_FALSE : CC_TRUE;
}


static combo_key first_binary(u32 len)
{
	combo_key bin(len, CC_FALSE);
	bin.back() = CC_TRUE;

	return bin;
}


static void next_binary(combo_key& bin)
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


static void skip_binary(combo_key& bin)
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


class ComboSizePair
{
public:
	combo_key bin;
	f32 size;
};


class ComboSizeList
{
private:
	std::vector<ComboSizePair> data;
	std::vector<u32> sorted_data_ids;

public:

	void add(combo_key const& bin, f32 size)
	{
		sorted_data_ids.push_back((u32)data.size());
		data.push_back({ bin, size });
	}


	u32 id_at(u32 offset) const
	{
		return sorted_data_ids[offset];
	}


	void remove_at(u32 offset)
	{
		auto begin = sorted_data_ids.begin();
		auto end = sorted_data_ids.end();
		auto data_id = id_at(offset);

		std::remove(begin, end, data_id);
	}


	void remove_common(combo_key const& bin)
	{
		for (auto it = sorted_data_ids.rbegin(); it != sorted_data_ids.rend(); --it)
		{
			auto offset = *it;
			auto& combo = data[sorted_data_ids[offset]].bin;
			if (has_common_bit(combo, bin))
			{
				remove_at(offset);
			}
		}
	}


	f32 size_at(u32 offset) const { return data[id_at(offset)].size; }

	u64 length() const { return sorted_data_ids.size(); }

	std::vector<ComboSizePair>& get_data() { return data; }
};


class ContainerCapacityList
{
private:
	std::vector<f32> data;
	std::vector<u32> sorted_data_ids;

public:

	void set_data(std::vector<f32> const& capacities)
	{
		data = capacities;
		sorted_data_ids.resize(data.size());
		auto begin = sorted_data_ids.begin();
		auto end = sorted_data_ids.end();
		std::iota(begin, end, 0);
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
		auto end = sorted_data_ids.end();
		auto data_id = id_at(offset);

		std::remove(begin, end, data_id);
	}


	f32 value_at(u32 offset) const
	{
		return data[id_at(offset)];
	}


	f32 max_value() const { return data[sorted_data_ids.back()]; }

	u64 length() const { return sorted_data_ids.size(); }
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


	f32 combo_size(combo_key const& bin) const
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


	std::vector<u32> combo_items(combo_key const& bin)
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


	u64 length() const { return sorted_data_ids.size(); }
};


#if 0
static f32 item_combo_size(u64 item_combo)
{
	f32 size = 0.0f;

	u64 p = 1;
	for (u32 i = 0; i < n_items; ++i, p *= 2)
	{
		if (p & item_combo)
		{
			size += item_size(i);
		}
	}

	return size;
}
#endif


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


class ComboCapacityMatch
{
public:
	u32 combo_offset = 0;
	u32 capacity_offset = 0;
};


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
			auto diff = capacities.value_at(cap_offset) - size;

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



namespace cut_calculator
{
	std::vector<ContainerItems> sort(std::vector<f32> const& item_sizes, std::vector<f32> const& container_capacities, f32 acc_diff)
	{
		ItemSizeList size_list;
		ContainerCapacityList capacity_list;

		size_list.set_data(item_sizes);
		size_list.sort();

		capacity_list.set_data(container_capacities);
		capacity_list.sort();

		auto combo_list = build_combos(size_list, capacity_list.max_value());

		std::vector<int> capacity_combos(capacity_list.length(), -1);

		while (combo_list.length() && capacity_list.length())
		{
			auto match = best_match(combo_list, capacity_list, acc_diff);

			auto capacity_id = capacity_list.id_at(match.capacity_offset);
			auto combo_id = combo_list.id_at(match.combo_offset);

			capacity_combos[capacity_id] = combo_id;

			capacity_list.remove_at(match.capacity_offset);
			combo_list.remove_at(match.combo_offset);
		}

		auto& combo_sizes = combo_list.get_data();
		std::vector<ContainerItems> result;

		for (int cap_id = 0; cap_id < capacity_combos.size(); ++cap_id)
		{
			auto combo_id = capacity_combos[cap_id];
			if (combo_id < 0)
			{
				continue;
			}

			auto& combo = combo_sizes[combo_id];

			ContainerItems res{};
			res.container_id = cap_id;
			res.container_capacity = container_capacities[cap_id];
			res.item_ids = size_list.combo_items(combo.bin);
			res.item_size = combo.size;

			result.push_back(std::move(res));
		}

		return result;
	}
}
