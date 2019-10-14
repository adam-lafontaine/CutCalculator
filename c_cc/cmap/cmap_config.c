#include <stdlib.h> 
#include "cmap_config.h"

// defines how a character is mapped to an array index
size_t c_idx(char* c) {
	return *c - 'a';
}