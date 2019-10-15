#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "cc_lib.h"

//======= HELPERS ==================

cc_combo_key copy_binary(cc_combo_key const binary) {
	cc_combo_key copy = (cc_combo_key)calloc(strlen(binary) + 1, sizeof(cc_bit_type));
	if (copy == NULL)
		return NULL;

	strcpy_s(copy, strlen(binary) + 1, binary);

	return copy;
}

//---------------------------

cc_combo_key new_zero_binary(size_t num_bits) {
	cc_combo_key binary = (cc_combo_key)calloc(num_bits + 1, sizeof(cc_bit_type));
	if (binary == NULL)
		return NULL;

	memset(binary, cc_false, num_bits);

	return binary;
}

//==================================

bool has_bit(cc_combo_key c) {
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

cc_combo_key to_binary(u_int_t value, unsigned num_bits) {
	cc_bit_type const bin_values[] = { cc_false, cc_true };

	unsigned const min_bits = (unsigned)(log2((double)value) + 1);
	if (min_bits > num_bits)
		num_bits = min_bits;

	cc_combo_key binary = new_zero_binary(num_bits);

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

u_int_t to_decimal(cc_combo_key binary) {
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

bool has_common_bit(cc_combo_key const bin_1, cc_combo_key const bin_2) {
	size_t last_1 = strlen(bin_1) - 1;
	size_t last_2 = strlen(bin_2) - 1;

	for (size_t i = 0; i <= last_1 && i <= last_2; ++i) {
		if (bin_1[last_1 - i] == cc_true && bin_2[last_2 - i] == cc_true)
			return true;
	}

	return false;
}

//--------------------------

cc_combo_key next_binary(cc_combo_key const binary) {
	cc_combo_key next_bin = copy_binary(binary);
	
	for (int i = strlen(binary) - 1; i >= 0 && (next_bin[i] = flip_bit(next_bin[i])) != cc_true; --i)
		;

	return next_bin;
}



//------------------------

cc_combo_key skip_binary(cc_combo_key const binary) {
	size_t num_bits = strlen(binary);
	cc_combo_key copy = copy_binary(binary);

	copy[num_bits - 1] = cc_true;

	int i = num_bits - 2;
	while (i >= 0 && copy[i] != cc_true)
		copy[i--] = cc_true;

	cc_combo_key next_bin = next_binary(copy);
	free(copy);

	return next_bin;
}