#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "cc_lib.h"

//======= HELPERS ==================

char* copy_binary(char* const binary) {
	char* copy = (char*)calloc(strlen(binary) + 1, sizeof(cc_bit_type));
	if (copy == NULL)
		return NULL;

	strcpy_s(copy, strlen(binary) + 1, binary);

	return copy;
}

//---------------------------

char* new_zero_binary(size_t num_bits) {
	char* binary = (char*)calloc(num_bits + 1, sizeof(cc_bit_type));
	if (binary == NULL)
		return NULL;

	binary[num_bits] = '\0';

	memset(binary, cc_false, num_bits);

	return binary;
}

//==================================

bool has_bit(char* c) {
	while (*c != '\0') {
		if (*c++ == cc_true)
			return true;
	}

	return false;
}

//--------------------------------


cc_bit_type flip_bit(cc_bit_type const bit) {
	return bit == cc_false ? cc_true : cc_false;
}

//-------------------------------

char* to_binary(u_int_t value, unsigned num_bits) {
	cc_bit_type const bin_values[] = { cc_false, cc_true };

	unsigned const min_bits = (unsigned)(log2((double)value) + 1);
	if (min_bits > num_bits)
		num_bits = min_bits;

	char* binary = new_zero_binary(num_bits);

	size_t bin_idx = num_bits;

	while (value > 0) {
		size_t idx = value % 2;
		binary[--bin_idx] = bin_values[idx];
		value -= idx;
		value /= 2;
	}

	return binary;
}

//-----------------------------

u_int_t to_decimal(char* binary) {
	u_int_t val = 0;
	int exp = 0;

	size_t pos = strlen(binary);

	while (pos > 0) {
		if (binary[--pos] == cc_true)
			val += (u_int_t)pow(2, exp);

		++exp;
	}

	return val;
}

//--------------------------

bool has_common_bit(char* const bin_1, char* const bin_2) {
	size_t last_1 = strlen(bin_1) - 1;
	size_t last_2 = strlen(bin_2) - 1;

	for (size_t i = 0; i <= last_1 && i <= last_2; ++i) {
		if (bin_1[last_1 - i] == cc_true && bin_2[last_2 - i] == cc_true)
			return true;
	}

	return false;
}

//--------------------------

char* next_binary(char* const binary) {
	char* next_bin = copy_binary(binary);
	
	for (int i = strlen(binary) - 1; i >= 0 && (next_bin[i] = flip_bit(next_bin[i])) != cc_true; --i)
		;

	return next_bin;
}



//------------------------

char* skip_binary(char* const binary) {
	size_t num_bits = strlen(binary);
	char* copy = copy_binary(binary);

	copy[num_bits - 1] = cc_true;

	int i = num_bits - 2;
	while (i >= 0 && copy[i] != cc_true)
		copy[i--] = cc_true;

	char* next_bin = next_binary(copy);
	free(copy);

	return next_bin;
}

cc_value_type cc_combo_size(char* const binary, piece_list* pieces, cc_value_type loss_per_piece) {
	cc_value_type result = 0;
	size_t num_bits = strlen(binary);
	size_t num_pieces = pieces->size;

	for (size_t i = 0; i < num_bits && i < num_pieces; ++i) {
		char bit = binary[num_bits - 1 - i];
		cc_value_type size = pieces->data[num_pieces - 1 - i]->size;
		if (bit == cc_true)
			result += size + loss_per_piece;
	}

	return result;
}

piece_list* cc_filter_pieces(char* const binary, piece_list* pieces) {
	size_t num_bits = strlen(binary);
	size_t num_pieces = pieces->size;

	piece_list* list = piece_list_create(num_pieces);

	for (size_t i = 0; i < num_bits && i < num_pieces; ++i) {
		char bit = binary[num_bits - 1 - i];
		if (bit == cc_true)
			piece_list_push_back(list, pieces->data[num_pieces - 1 - i]);
	}

	return list;
}

cc_value_type cc_max_capacity(container_list* containers) {
	if (containers->size == 0)
		return 0;

	// last element because list is sorted
	return containers->data[containers->size - 1]->capacity;
}

cmap* cc_build_piece_combos(container_list* containers, piece_list* pieces, cc_value_type loss) {
	cmap* piece_combos = cmap_create();

	cc_value_type max_cap = cc_max_capacity(containers);
	char* binary = to_binary(1, pieces->size);

	while (has_bit(binary)) {
		cc_value_type size = cc_combo_size(binary, pieces, loss);
		if (size <= max_cap) {
			cmap_add(piece_combos, binary, size);
			binary = next_binary(binary);
		}
		else {
			char* ptr = binary;
			binary = skip_binary(binary);
			free(ptr);
		}
	}

	free(binary);

	return piece_combos;
}

result* cc_best_match(container_list* containers, piece_list* pieces, cmap* piece_combos, ccvt loss, ccvt tolerance) {
	if (containers->size == 0)
		return NULL;

	cc_value_type max_cap = cc_max_capacity(containers);
	cc_value_type best_diff = max_cap;
	size_t best_ct_idx = 0;
	char* best_binary = NULL;

	for (piece_combo* pc = cmap_get_first(piece_combos); pc != NULL; pc = cmap_get_next(piece_combos, pc->binary)) {
		char* binary = pc->binary;
		cc_value_type size = pc->combo_size;

		for (size_t ct_idx = 0; ct_idx < containers->size; ++ct_idx) {
			container* ct = containers->data[ct_idx];
			cc_value_type diff = ct->capacity - size;

			bool is_better_diff = (-1 * loss) <= diff && diff < best_diff;

			if (!is_better_diff)
				continue;

			best_diff = diff;
			best_ct_idx = ct_idx;
			best_binary = binary;

			if (diff > tolerance)
				continue;

			return result_create(
				cmap_remove(piece_combos, best_binary),
				cc_filter_pieces(best_binary, pieces),
				container_list_remove(containers, best_ct_idx),
				best_diff);
		}
	}

	return result_create(
		cmap_remove(piece_combos, best_binary),
		cc_filter_pieces(best_binary, pieces),
		container_list_remove(containers, best_ct_idx),
		best_diff);
}

void cc_remove_combos(cmap* piece_combos, char* const binary, container_list* containers) {

	bool has_max = containers->size > 0;
	cc_value_type max_cap = has_max ? cc_max_capacity(containers) : 0;

	piece_combo* next_pc;
	for (piece_combo* pc = cmap_get_first(piece_combos); pc != NULL; pc = next_pc) {
		next_pc = cmap_get_next(piece_combos, pc->binary); // get next before this is erased

		if (pc->combo_size > max_cap || has_common_bit(pc->binary, binary))
			cmap_erase(piece_combos, pc->binary);			
	}

}

cc_sort_dto* cc_sort(container_list* containers, piece_list* pieces, ccvt loss, ccvt tolerance) {

	cmap* piece_combos = cc_build_piece_combos(containers, pieces, loss);

	result_list* sorted = result_list_create(10);

	while (containers->size > 0 && !cmap_empty(piece_combos)) {
		result* match = cc_best_match(containers, pieces, piece_combos, loss, tolerance);
		cc_remove_combos(piece_combos, match->combo->binary, containers);
		result_list_push_back(sorted, match);
	}

	bool success = cmap_empty(piece_combos);
	char* message = success ? "solution found" : "not enough containers";

	cmap_destroy(piece_combos);		

	cc_sort_dto* dto = cc_sort_dto_create(sorted, success, message);

	return dto;
}