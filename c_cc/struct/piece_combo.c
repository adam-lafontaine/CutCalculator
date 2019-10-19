#include <stdlib.h>
#include "piece_combo.h"

piece_combo* piece_combo_create(cc_combo_key binary, cc_value_type combo_size) {
	piece_combo* combo = (piece_combo*)malloc(sizeof(piece_combo));
	if (combo == NULL)
		return NULL;

	combo->binary = binary;
	combo->combo_size = combo_size;

	return combo;
}

void piece_combo_destroy(piece_combo* pc_combo) {
	if (pc_combo->binary != NULL)
		free(pc_combo->binary);

	free(pc_combo);
}