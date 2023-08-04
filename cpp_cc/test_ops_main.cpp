#include "cut_calculator.hpp"

#include <cstdio>

namespace cc = cut_calculator;


static void print(std::vector<f32> const& items, std::vector<f32> const& containers, std::vector<cc::ContainerItems> const& result)
{
	printf("\n");
	printf("items:");
	for (auto n : items)
	{
		printf(" %f", n);
	}
	printf("\n\n");

	printf("containers:");
	for (auto n : containers)
	{
		printf(" %f", n);
	}
	printf("\n\n");

	printf("results:\n");
	for (auto const& r : result)
	{
		printf("container %u: %f/%f\n", r.container_id, r.container_capacity, containers[r.container_id]);
		printf("items: [");
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
}




static bool test_stuff()
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

	return true;
}

int main()
{
	if (!cc::test_binary_ops())
	{
		return 1;
	}

	test_stuff();

	return 0;
}