#ifndef __RESULT_H__
#define __RESULT_H__

#include <ctype.h>
#include <stdbool.h>

#include "../cc_types.h"

typedef struct Result {
	//char* binary; // needed?
	piece_combo* combo;
	piece_list* pieces;
	container* container;
	cc_value_type delta;

} result;

typedef result** result_ptr_array;

typedef struct ResultList {
	result_ptr_array   data;
	size_t        size;
	size_t        capacity;
} result_list;

result* result_create(piece_combo* combo, piece_list* pieces, container* container, cc_value_type delta);

void result_destroy(result* pc);

result_list* result_list_create(size_t capacity);

void result_list_destroy(result_list* list);

bool result_list_push_back(result_list* list, result* value);


#endif // !__RESULT_H__
