#ifndef __CC_LIB_H__
#define __CC_LIB_H__

#include <stdbool.h>

#include "cmap/cmap.h"
#include "struct/piece.h"
#include "struct/container.h"
#include "struct/piece_combo.h"
#include "struct/result.h"
#include "struct/cc_sort_dto.h"

static const cc_bit_type cc_false = '0';
static const cc_bit_type cc_true = '1';


// binary functions
bool has_bit(char* binary);
cc_bit_type flip_bit(cc_bit_type const bit);
char* to_binary(u_int_t value, unsigned num_bits);
u_int_t to_decimal(char* binary);
bool has_common_bit(char* const bin_1, char* const bin_2);
char* next_binary(char* const binary);
char* skip_binary(char* const binary);


cc_value_type cc_combo_size(char* const binary, piece_list* pieces, cc_value_type loss_per_piece);
piece_list* cc_filter_pieces(char* const binary, piece_list* pieces);








#endif