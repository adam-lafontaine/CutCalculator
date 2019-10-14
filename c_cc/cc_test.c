#include <stdlib.h>
#include <string.h>

#include "cc_test.h"
#include "cmap/cmap.h"

// set map value type
typedef int cmap_value_t;

//======= HELPERS ==============================

void print_sub(const char* msg, unsigned level) {
	printf("%*s%s",
		level, "  ", msg);
}


//======= TESTS ================================

bool test_has_bit() { 
	puts("\ntest_has_bit():");
	print_sub("Not Implemented\n", 1);

	

	return false;
}

bool test_flip_bit() { puts("\ntest_flip_bit():"); print_sub("Not Implemented\n", 1); return false; }

bool test_to_binary() { puts("\ntest_to_binary():"); print_sub("Not Implemented\n", 1); return false; }

bool test_to_decimal() { puts("\ntest_to_decimal():"); print_sub("Not Implemented\n", 1); return false; }

bool test_has_common_bit() { puts("\ntest_has_common_bit():"); print_sub("Not Implemented\n", 1); return false; }

bool test_next_binary() { puts("\ntest_next_binary():"); print_sub("Not Implemented\n", 1); return false; }

bool test_skip_binary() { puts("\ntest_skip_binary():"); print_sub("Not Implemented\n", 1); return false; }

bool test_pieces() { puts("\ntest_pieces():"); print_sub("Not Implemented\n", 1); return false; }

bool test_containers() { puts("\ntest_containers():"); print_sub("Not Implemented\n", 1); return false; }

bool test_combo_size() { puts("\ntest_combo_size():"); print_sub("Not Implemented\n", 1); return false; }

bool test_filter_pieces() { puts("\ntest_filter_pieces():"); print_sub("Not Implemented\n", 1); return false; }

bool test_max_capacity() { puts("\ntest_max_capacity():"); print_sub("Not Implemented\n", 1); return false; }

bool test_build_piece_combos() { puts("\ntest_build_piece_combos():"); print_sub("Not Implemented\n", 1); return false; }

bool test_best_match() { puts("\ntest_best_match():"); print_sub("Not Implemented\n", 1); return false; }

bool test_remove_combos() { puts("\ntest_remove_combos():"); print_sub("Not Implemented\n", 1); return false; }

bool test_sort() { puts("\ntest_sort():"); print_sub("Not Implemented\n", 1); return false; }


//==============================

/*

bool test_create_destroy() {
	puts("\ntest_create_destroy():");

	unsigned level = 1;
	bool result = true;

	cmap* map = cmap_create();
	if (result = (map != NULL))
		print_sub("create ok\n", level);
	else
		print_sub("create failed\n", level);

	cmap_destroy(map);
	print_sub("destroy ok\n", level);

	return result;
}

*/