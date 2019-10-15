#ifndef __CC_LIB_H__
#define __CC_LIB_H__

#include <stdbool.h>

typedef char* cc_combo_key;
typedef char cc_bit_type;
typedef unsigned long long u_int_t;

static const cc_bit_type cc_false = '0';
static const cc_bit_type cc_true = '1';


// binary functions
bool has_bit(cc_combo_key binary);
cc_bit_type flip_bit(cc_bit_type const bit);
cc_combo_key to_binary(u_int_t value, unsigned num_bits);
u_int_t to_decimal(cc_combo_key binary);
bool has_common_bit(cc_combo_key const bin_1, cc_combo_key const bin_2);
cc_combo_key next_binary(cc_combo_key const binary);
cc_combo_key skip_binary(cc_combo_key const binary);

#endif