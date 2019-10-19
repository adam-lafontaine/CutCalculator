#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "cc_test.h"
#include "cmap/cmap.h"
#include "cc_lib.h"

//======= HELPERS ==============================

void print_sub(const char* msg, unsigned level) {
	printf("%*s%s",
		level, "  ", msg);
}


//======= TESTS ================================

bool test_has_bit() { 
	puts("\ntest_has_bit():");

	size_t num_ele = 5;
	char* source[] = { "01110", "000", "1010110", "0000000", "0001000" };
	bool expected[] = { true, false, true, false, true };

	bool result = true;
	for (size_t i = 0; i < num_ele; ++i)
		result &= has_bit(source[i]) == expected[i];

	if (result)
		print_sub("has_bit ok\n", 1);
	else
		print_sub("has_bit fail\n", 1);

	return result;
}

bool test_flip_bit() { 
	puts("\ntest_flip_bit():"); 

	size_t num_ele = 2;
	char source[] = { '0', '1' };
	char expected[] = { '1', '0' };

	bool result = true;
	for (size_t i = 0; i < num_ele; ++i)
		result &= flip_bit(source[i]) == expected[i];

	if (result)
		print_sub("flip_bit ok\n", 1);
	else
		print_sub("flip_bit fail\n", 1);

	return result;
}

bool test_to_binary() { 
	puts("\ntest_to_binary():"); 

	size_t num_ele = 5;
	unsigned values[] = { 3205, 55, 55, 3205, 1 };
	unsigned lengths[] = { 12, 6, 12, 5, 12 };
	cc_combo_key expected[] = { "110010000101", "110111", "000000110111", "110010000101", "000000000001" };

	bool result = true;
	for (size_t i = 0; i < num_ele; ++i) {
		cc_combo_key binary = to_binary(values[i], lengths[i]);
		cc_combo_key exp = expected[i];
		result &= binary != NULL && strcmp(binary, exp) == 0;

		free(binary);
	}
		

	if (result)
		print_sub("to_binary ok\n", 1);
	else
		print_sub("to_binary fail\n", 1);
	
	return result; 
}

bool test_to_decimal() { 
	puts("\ntest_to_decimal():");

	size_t num_ele = 7;
	cc_combo_key binarys[] = 
	{ "1011", "100011", "0000000", "1001001110001", "00001011", "0000100011", "00001001001110001" };

	unsigned expected[] = { 11, 35, 0, 4721, 11, 35, 4721 };

	bool result = true;
	for (size_t i = 0; i < num_ele; ++i)
		result &= to_decimal(binarys[i]) == expected[i];

	if (result)
		print_sub("to_decimal ok\n", 1);
	else
		print_sub("to_decimal fail\n", 1);

	return result; 
}

bool test_has_common_bit() { 
	puts("\ntest_has_common_bit():");
	
	size_t num_ele = 5;
	cc_combo_key bin_1[] = { "0", "0", "100110", "0100110011", "1001001" };
	cc_combo_key bin_2[] = { "0", "1", "000100", "0010", "0110110" };
	bool expected[] = { false, false, true, true, false };

	bool result = true;
	for (size_t i = 0; i < num_ele; ++i)
		result &= has_common_bit(bin_1[i], bin_2[i]) == expected[i];

	if (result)
		print_sub("has_common_bit ok\n", 1);
	else
		print_sub("has_common_bit fail\n", 1);
	
	return result; 
}

bool test_next_binary() { 
	puts("\ntest_next_binary():"); 

	size_t num_ele = 5;
	cc_combo_key bin[] = { "1011", "100011", "0000000", "11111", "0010010" };
	cc_combo_key expected[] = { "1100", "100100", "0000001", "00000", "0010011" };

	bool result = true;
	for (size_t i = 0; i < num_ele; ++i) {
		cc_combo_key next_bin = next_binary(bin[i]);
		result &= strcmp(next_bin, expected[i]) == 0;

		free(next_bin);
	}
		

	if (result)
		print_sub("next_binary ok\n", 1);
	else
		print_sub("next_binary fail\n", 1);

	return result; 
}

bool test_skip_binary() { 
	puts("\ntest_skip_binary():"); 
	
	size_t num_ele = 3;
	cc_combo_key bin[] = { "1100100", "0010001000", "11111" };
	cc_combo_key expected[] = { "1101000", "0010010000", "00000" };

	bool result = true;
	for (size_t i = 0; i < num_ele; ++i) {
		cc_combo_key next_bin = skip_binary(bin[i]);
		result &= strcmp(next_bin, expected[i]) == 0;

		free(next_bin);
	}


	if (result)
		print_sub("skip_binary ok\n", 1);
	else
		print_sub("skip_binary fail\n", 1);

	return result;
}

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