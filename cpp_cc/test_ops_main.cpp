#include "cut_calculator.hpp"

#include <cstdio>
#include <algorithm>

namespace cc = cut_calculator;


static void print(std::vector<f32> const& items, std::vector<f32> const& containers, cc::SortResult const& result)
{
	printf("\n");
	printf("     items:");
	for (auto n : items)
	{
		printf(" %f", n);
	}
	printf("\n");

	printf("containers:");
	for (auto n : containers)
	{
		printf(" %f", n);
	}
	printf("\n\n");

	printf("results:\n");
	for (auto const& r : result.sorted)
	{
		printf("container [ %u ]: %f/%f\n", r.container_id, r.container_capacity, containers[r.container_id]);
		printf("    items [");
		for (auto i : r.item_ids)
		{
			printf(" %u", i);
		}
		printf(" ]: [");
		
		for (auto i : r.item_ids)
		{
			printf(" %f", items[i]);
		}
		printf(" ] = %f\n\n", r.item_size);
	}

	printf("unsorted_containers [");
	for (auto i : result.unsorted_container_ids)
	{
		printf(" %u", i);
	}
	printf(" ]: [");

	for (auto i : result.unsorted_container_ids)
	{
		printf(" %f", containers[i]);
	}
	printf(" ]\n");

	printf("     unsorted items [");
	for (auto i : result.unsorted_item_ids)
	{
		printf(" %u", i);
	}
	printf(" ]: [");

	for (auto i : result.unsorted_item_ids)
	{
		printf(" %f", items[i]);
	}
	printf(" ]\n\n");	
}


static bool test_container_ids(std::vector<f32> const& containers, cc::SortResult const& sort_result)
{	
	std::vector<u32> ids;

	for (auto const& c : sort_result.sorted)
	{
		ids.push_back(c.container_id);
	}

	for (auto c : sort_result.unsorted_container_ids)
	{
		ids.push_back(c);
	}

	if (ids.size() != containers.size())
	{
		return false;
	}

	std::sort(ids.begin(), ids.end());

	for (u32 i = 0; i < (u32)ids.size(); ++i)
	{
		if (ids[i] != i)
		{
			return false;
		}
	}

	return true;
}


static void test_sort_results(std::vector<f32> const& items, std::vector<f32> const& containers, cc::SortResult const& sort_result)
{
	auto result = true;

	result &= test_container_ids(containers, sort_result);

	if (result)
	{
		printf("sort_result: OK\n");
	}
}


static void test_easy()
{
	std::vector<f32> container_capacities
	{
		7, 22, 39
	};


	std::vector<f32> item_sizes
	{
		7, 
		11, 11, 
		13, 13, 13
	};
	
	auto result = cc::sort(item_sizes, container_capacities);

	print(item_sizes, container_capacities, result);
	test_sort_results(item_sizes, container_capacities, result);
}

int main()
{
	if (!cc::test_binary_ops())
	{
		return 1;
	}

	test_easy();

	return 0;
}