#ifndef __BIN_BUILDER_H__
#define __BIN_BUILDER_H__

struct bin_builder;
typedef struct bin_builder bin_builder_t;

bin_builder_t* bin_builder_create(unsigned int num_bits);


#endif /* __BIN_BUILDER_H__ */