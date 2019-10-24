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