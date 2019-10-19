#include <stdlib.h>

#include "container.h"

#define LIST_BLOCK_SIZE 64

container* container_create(cc_value_type cap) {
	container* pc = (container*)malloc(sizeof(container));
	if (pc == NULL)
		return NULL;

	pc->capacity = cap;

	return pc;
}

void container_destroy(container* cont) {
	if (cont != NULL)
		free(cont);
}


container_list* container_list_create(size_t list_capacity) {
	container_list* list = (container_list*)malloc(sizeof(container_list));
	if (list == NULL)
		return NULL;

	list->capacity = list_capacity;
	list->size = 0;

	container_ptr_array block = (container_ptr_array)calloc(list_capacity, sizeof(container*));
	if (block == NULL)
		return NULL;

	list->data = block;

	return list;
}

void container_ptr_array_destroy(container_ptr_array data, size_t size) {
	if (data == NULL)
		return;

	for (size_t i = 0; i < size; ++i) {
		container_destroy((container*)data[i]);
	}

	free(data);
}

void container_list_destroy(container_list* list) {
	if (list == NULL)
		return;

	if (list->data != NULL)
		container_ptr_array_destroy(list->data, list->size);

	free(list);
}

bool container_list_push_back(container_list* list, container* value) {

	if (list->size == list->capacity) {
		size_t cap = list->capacity;
		size_t new_capacity = cap + LIST_BLOCK_SIZE;

		container_ptr_array block = (container_ptr_array)realloc(list->data, new_capacity * sizeof(container*));
		if (block == NULL)
			return false;

		list->data = block;
		list->capacity = new_capacity;
	}

	list->data[list->size++] = value;

	return true;
}

int compare_asc(const void* p_lhs, const void* p_rhs) {

	const container* lhs = (const container*)p_lhs;
	const container* rhs = (const container*)p_rhs;

	if (lhs->capacity < rhs->capacity) return -1;
	if (lhs->capacity > rhs->capacity) return 1;
	return 0;
}

void container_list_sort_asc(container_list* list) {
	qsort(list->data, list->size, sizeof(container*), compare_asc);
}