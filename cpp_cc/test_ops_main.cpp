#include "cut_calculator.hpp"

#include <cstdio>
#include <algorithm>

namespace cc = cut_calculator;


static void print(std::vector<f32> const& items, std::vector<f32> const& containers, cc::SortResult const& result)
{
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
		printf("container_ids: bad count\n");
		return false;
	}

	std::sort(ids.begin(), ids.end());

	for (u32 i = 0; i < (u32)ids.size(); ++i)
	{
		if (ids[i] != i)
		{
			printf("container_ids: bad id\n");
			return false;
		}
	}

	return true;
}


static bool test_container_capacities(std::vector<f32> const& containers, cc::SortResult const& sort_result)
{
	for (auto const& c : sort_result.sorted)
	{
		if (c.container_capacity != containers[c.container_id])
		{
			printf("container_capacities: bad capacity\n");
			return false;
		}

		return true;
	}
}


static bool test_item_ids(std::vector<f32> const& items, cc::SortResult const& sort_result)
{
	std::vector<u32> ids;

	for (auto const& c : sort_result.sorted)
	{
		for (auto i : c.item_ids)
		{
			ids.push_back(i);
		}		
	}

	for (auto i : sort_result.unsorted_item_ids)
	{
		ids.push_back(i);
	}

	if (ids.size() != items.size())
	{
		printf("item_ids: bad count\n");
		return false;
	}

	std::sort(ids.begin(), ids.end());

	for (u32 i = 0; i < (u32)ids.size(); ++i)
	{
		if (ids[i] != i)
		{
			printf("item_ids: bad id\n");
			return false;
		}
	}

	return true;
}


static bool test_item_sizes(std::vector<f32> const& items, cc::SortResult const& sort_result)
{
	for (auto const& c : sort_result.sorted)
	{
		f32 size = 0.0f;
		for (auto i : c.item_ids)
		{
			size += items[i];
		}

		if (c.item_size != size)
		{
			printf("item_sizes: bad size\n");
			return false;
		}
	}

	return true;
}


static bool test_capacity_item_size(cc::SortResult const& sort_result)
{
	for (auto const& c : sort_result.sorted)
	{
		if (c.container_capacity < c.item_size)
		{
			printf("capacity_item_size: bad container capacity/item size\n");
			return false;
		}
	}

	return true;
}


static bool test_unsorted(std::vector<f32> const& items, std::vector<f32> const& containers, cc::SortResult const& sort_result)
{
	for (auto const& r : sort_result.sorted)
	{
		auto leftover = r.container_capacity - r.item_size;
		for (auto i : sort_result.unsorted_item_ids)
		{
			if (items[i] <= leftover)
			{
				printf("unsorted: unsorted item\n");
				return false;
			}
		}
	}

	for (auto c : sort_result.unsorted_container_ids)
	{
		for (auto i : sort_result.unsorted_item_ids)
		{
			if (containers[c] >= items[i])
			{
				printf("unsorted: unused container\n");
				return false;
			}
		}
	}

	return true;
}


static void test_sort_results(std::vector<f32> const& items, std::vector<f32> const& containers, cc::SortResult const& sort_result)
{
	auto result = true;

	result &= test_container_ids(containers, sort_result);
	result &= test_container_capacities(containers, sort_result);
	result &= test_item_ids(items, sort_result);
	result &= test_item_sizes(items, sort_result);
	result &= test_capacity_item_size(sort_result);
	result &= test_unsorted(items, containers, sort_result);

	if (result)
	{
		printf("\nsort_result: OK\n");
	}
}


static void test_easy()
{
	std::vector<f32> container_capacities
	{
		39, 22, 7
	};

	std::vector<f32> item_sizes
	{
		13, 13, 13,
		7, 
		11, 11,		
	};
	
	auto result = cc::sort(item_sizes, container_capacities);

	test_sort_results(item_sizes, container_capacities, result);
	print(item_sizes, container_capacities, result);	
}


static void test_extra_containers()
{
	std::vector<f32> container_capacities
	{
		39, 22, 7, 12, 34, 6
	};

	std::vector<f32> item_sizes
	{
		13, 13, 13,
		7,
		11, 11,
	};

	auto result = cc::sort(item_sizes, container_capacities);

	test_sort_results(item_sizes, container_capacities, result);
	print(item_sizes, container_capacities, result);
}


static void test_extra_items()
{
	std::vector<f32> container_capacities
	{
		39, 22, 7
	};

	std::vector<f32> item_sizes
	{
		13, 13, 13,
		7,
		11, 11,
		12, 5, 4
	};

	auto result = cc::sort(item_sizes, container_capacities);

	test_sort_results(item_sizes, container_capacities, result);
	print(item_sizes, container_capacities, result);
}


static void test_many_items()
{
	/*std::vector<f32> container_capacities
	{
		75, 111, 147, 183, 219, 255
	};

	std::vector<f32> item_sizes
	{
		10, 16, 22, 28, 34, 40,
		11, 17, 23, 29, 35, 41, 
		12, 18, 24, 30, 36, 42,
		13, 19, 25, 31, 37, 43,
		14, 20, 26, 32, 38, 44,
		15, 21, 27, 33, 39, 45,
	};*/

	std::vector<f32> container_capacities
	{
		147, 183, 219, 255
	};

	std::vector<f32> item_sizes
	{
		22, 28, 34, 40,
		23, 29, 35, 41,
		24, 30, 36, 42,
		25, 31, 37, 43,
		26, 32, 38, 44,
		27, 33, 39, 45,
	};

	/*std::vector<f32> container_capacities
	{
		183, 219, 255
	};

	std::vector<f32> item_sizes
	{
		28, 34, 40,
		29, 35, 41,
		30, 36, 42,
		31, 37, 43,
		32, 38, 44,
		33, 39, 45,
	};*/

	auto result = cc::sort(item_sizes, container_capacities);

	test_sort_results(item_sizes, container_capacities, result);
	print(item_sizes, container_capacities, result);
}


int main()
{
	if (!cc::test_binary_ops())
	{
		return 1;
	}

	//test_easy();
	//test_extra_containers();
	//test_extra_items();
	//test_many_items();

	return 0;
}