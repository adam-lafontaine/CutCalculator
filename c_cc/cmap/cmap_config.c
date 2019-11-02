#include <stdlib.h> 
#include "cmap_config.h"

// defines how a character is mapped to an array index
size_t c_idx(char* c) {

	//return *c - '0';

	// inserts in map in reverse order
	switch (*c) {
	case '1':
		return 0;
	case '0':
		return 1;
	}

	return 2; // breaks
}