#ifndef __PIECE_H__
#define __PIECE_H__

#include <ctype.h>
#include <stdbool.h>

#include "../cc_types.h"

typedef struct Piece {

	cc_value_type size;
	// other properties
} piece;

typedef piece** piece_ptr_array;

typedef struct PieceList {
	piece_ptr_array   data;
	size_t        size;
	size_t        capacity;
} piece_list;

piece* piece_create(cc_value_type size);

void piece_destroy(piece* pc);

piece_list* piece_list_create(size_t capacity);

void piece_list_destroy(piece_list* list);

bool piece_list_push_back(piece_list* list, piece* value);

void piece_list_sort_desc(piece_list* list);

#endif // !__PIECE_H__
