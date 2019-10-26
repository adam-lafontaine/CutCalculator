#include <stdlib.h>
#include "piece.h"

#define LIST_BLOCK_SIZE 64

piece* piece_create(cc_value_type size) {
	piece* pc = (piece*)malloc(sizeof(piece));
	if (pc == NULL)
		return NULL;

	pc->size = size;

	return pc;
}

void piece_destroy(piece* pc) {
	if(pc != NULL)
		free(pc);
}


piece_list* piece_list_create(size_t capacity) {
	piece_list* list = (piece_list*)malloc(sizeof(piece_list));
	if (list == NULL)
		return NULL;

	list->capacity = capacity;
	list->size = 0;

	piece_ptr_array block = (piece_ptr_array)calloc(capacity, sizeof(piece*));
	if (block == NULL)
		return NULL;

	for (size_t i = 0; i < capacity; ++i)
		block[i] = NULL;

	list->data = block;

	return list;
}

void piece_ptr_array_destroy(piece_ptr_array data, size_t size) {
	if (data == NULL)
		return;

	for (size_t i = 0; i < size; ++i) {
		piece_destroy(data[i]);
	}

	free(data);
}

void piece_list_destroy(piece_list* list) {
	if (list == NULL)
		return;

	if (list->data != NULL)
		piece_ptr_array_destroy(list->data, list->size);

	free(list);
}

void piece_list_destroy_copy(piece_list* list) {
	if (list == NULL || list->data == NULL)
		return;

	free(list->data);
	free(list);
}

bool piece_list_push_back(piece_list* list, piece* value) {	

	if (list->size == list->capacity) {
		size_t cap = list->capacity;
		size_t new_capacity = cap + LIST_BLOCK_SIZE;

		piece_ptr_array block = (piece_ptr_array)realloc(list->data, new_capacity * sizeof(piece*));
		if (block == NULL)
			return false;

		list->data = block;
		list->capacity = new_capacity;
	}

	list->data[list->size++] = value;

	return true;
}

int compare_desc(const void* p_lhs, const void* p_rhs) {

	const piece* lhs = *(const piece**)p_lhs;
	const piece* rhs = *(const piece**)p_rhs;

	if (lhs->size < rhs->size) return 1;
	if (lhs->size > rhs->size) return -1;
	return 0;
}

void piece_list_sort_desc(piece_list* list) {
	qsort(list->data, list->size, sizeof(piece*), compare_desc);
}