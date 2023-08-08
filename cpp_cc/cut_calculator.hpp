#pragma once

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


#include <vector>


namespace cut_calculator
{
	class ContainerItems
	{
	public:
		u32 container_id = 0;
		std::vector<u32> item_ids;

		f32 container_capacity = 0.0f;
		f32 item_size = 0.0f;
	};


	class SortResult
	{
	public:

		std::vector<ContainerItems> sorted;

		std::vector<u32> unsorted_container_ids;
		std::vector<u32> unsorted_item_ids;
	};


	SortResult sort(std::vector<f32> const& item_sizes, std::vector<f32> const& container_capacities);


	bool test_binary_ops();
}

