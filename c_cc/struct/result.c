#include <stdlib.h>
#include "result.h"

#define LIST_BLOCK_SIZE 64

void piece_combo_destroy(piece_combo* pc_combo);
void piece_list_destroy(piece_list* list);
void container_destroy(container* pc);

result* result_create(piece_combo* combo, piece_list* pieces, container* container, cc_value_type delta) {
	result* res = (result*)malloc(sizeof(result));
	if (res == NULL)
		return NULL;

	res->binary = ""; // combo->binary
	res->combo = combo;
	res->pieces = pieces;
	res->container = container;
	res->delta = delta;

	return res;
}

void result_destroy(result* res) {
	if (res == NULL)
		return;

	piece_combo_destroy(res->combo);
	piece_list_destroy(res->pieces);
	container_destroy(res->container);
}


result_list* result_list_create(size_t capacity) {
	result_list* list = (result_list*)malloc(sizeof(result_list));
	if (list == NULL)
		return NULL;

	list->capacity = capacity;
	list->size = 0;

	result_ptr_array block = (result_ptr_array)calloc(capacity, sizeof(result*));
	if (block == NULL)
		return NULL;

	list->data = block;

	return list;
}

void result_ptr_array_destroy(result_ptr_array data, size_t size) {
	if (data == NULL)
		return;

	for (size_t i = 0; i < size; ++i) {
		result_destroy((result*)data[i]);
	}

	free(data);
}

void result_list_destroy(result_list* list) {
	if (list == NULL)
		return;

	if (list->data != NULL)
		result_ptr_array_destroy(list->data, list->size);

	free(list);
}

bool result_list_push_back(result_list* list, result* value) {

	if (list->size == list->capacity) {
		size_t cap = list->capacity;
		size_t new_capacity = cap + LIST_BLOCK_SIZE;

		result_ptr_array block = (result_ptr_array)realloc(list->data, new_capacity * sizeof(result*));
		if (block == NULL)
			return false;

		list->data = block;
		list->capacity = new_capacity;
	}

	list->data[list->size++] = value;

	return true;
}