#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <ctype.h>
#include <stdbool.h>

#include "../cc_types.h"

typedef struct Container {

	cc_value_type capacity;
	// other properties
} container;

typedef container** container_ptr_array;

typedef struct ContainerList {
	container_ptr_array   data;
	size_t        size;
	size_t        capacity;
} container_list;

container* container_create(cc_value_type size);

void container_destroy(container* ct);

container_list* container_list_create(size_t capacity);

void container_list_destroy(container_list* list);

bool container_list_push_back(container_list* list, container* value);

void container_list_sort_asc(container_list* list);

void container_list_erase(container_list* list, size_t index);

container* container_list_remove(container_list* list, size_t index);


#endif // !__CONTAINER_H__



