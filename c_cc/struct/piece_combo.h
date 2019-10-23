#ifndef __PIECE_COMBO_H__
#define __PIECE_COMBO_H__

#include "../cc_types.h"

typedef struct PieceCombo {

	char* binary;
	cc_value_type combo_size;
	
} piece_combo;


piece_combo* piece_combo_create(const char* binary, cc_value_type combo_size);

void piece_combo_destroy(piece_combo* pc_combo);

#endif // !__PIECE_COMBO_H__

