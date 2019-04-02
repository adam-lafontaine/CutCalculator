#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "bin_builder.h"

static const size_t BIN_BUILDER_MAX_32 = 4;

struct bin_32_bit {
   unsigned int bit_1 : 1;
   unsigned int bit_2 : 1;
   unsigned int bit_3 : 1;
   unsigned int bit_4 : 1;
   unsigned int bit_5 : 1;
   unsigned int bit_6 : 1;
   unsigned int bit_7 : 1;
   unsigned int bit_8 : 1;
   unsigned int bit_9 : 1;
   unsigned int bit_10 : 1;
   unsigned int bit_11 : 1;
   unsigned int bit_12 : 1;
   unsigned int bit_13 : 1;
   unsigned int bit_14 : 1;
   unsigned int bit_15 : 1;
   unsigned int bit_16 : 1;
   unsigned int bit_17 : 1;
   unsigned int bit_18 : 1;
   unsigned int bit_19 : 1;
   unsigned int bit_20 : 1;
   unsigned int bit_21 : 1;
   unsigned int bit_22 : 1;
   unsigned int bit_23 : 1;
   unsigned int bit_24 : 1;
   unsigned int bit_25 : 1;
   unsigned int bit_26 : 1;
   unsigned int bit_27 : 1;
   unsigned int bit_28 : 1;
   unsigned int bit_29 : 1;
   unsigned int bit_30 : 1;
   unsigned int bit_31 : 1;
   unsigned int bit_32 : 1;
};



struct bin_builder {

    struct bin_32_bit* binary[BIN_BUILDER_MAX_32];

};

bin_builder_t* bin_builder_create(unsigned int num_bits) {

    bin_builder_t* b;

    uint8_t num_bins = num_bits / 32;



    return b;
}