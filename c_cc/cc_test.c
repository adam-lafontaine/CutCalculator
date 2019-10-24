#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "cc_test.h"
#include "cmap/cmap.h"
#include "cc_lib.h"

//======= HELPERS ==============================

void print_sub(const char* msg, unsigned level) {
	printf("%*s%s",
		level, "  ", msg);
}

piece_list* piece_factory(size_t num, ...) {

	va_list ap;
	cc_value_type val;

	piece_list* list = piece_list_create(num);
	if (list == NULL)
		return NULL;

	va_start(ap, num);

	for (size_t i = 0; i < num; i++) {
		val = va_arg(ap, cc_value_type);
		piece* pc = piece_create(val);
		piece_list_push_back(list, pc);
	}

	va_end(ap);

	return list;
}


container_list* container_factory(size_t num, ...) {

	va_list ap;
	cc_value_type val;

	container_list* list = container_list_create(num);
	if (list == NULL)
		return NULL;

	va_start(ap, num);

	for (size_t i = 0; i < num; i++) {
		val = va_arg(ap, cc_value_type);
		container* pc = container_create(val);
		container_list_push_back(list, pc);
	}

	va_end(ap);

	return list;
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
	char* expected[] = { "110010000101", "110111", "000000110111", "110010000101", "000000000001" };

	bool result = true;
	for (size_t i = 0; i < num_ele; ++i) {
		char* binary = to_binary(values[i], lengths[i]);
		char* exp = expected[i];
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
	char* binarys[] = 
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
	char* bin_1[] = { "0", "0", "100110", "0100110011", "1001001" };
	char* bin_2[] = { "0", "1", "000100", "0010", "0110110" };
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
	char* bin[] = { "1011", "100011", "0000000", "11111", "0010010" };
	char* expected[] = { "1100", "100100", "0000001", "00000", "0010011" };

	bool result = true;
	for (size_t i = 0; i < num_ele; ++i) {
		char* next_bin = next_binary(bin[i]);
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
	char* bin[] = { "1100100", "0010001000", "11111" };
	char* expected[] = { "1101000", "0010010000", "00000" };

	bool result = true;
	for (size_t i = 0; i < num_ele; ++i) {
		char* next_bin = skip_binary(bin[i]);
		result &= strcmp(next_bin, expected[i]) == 0;

		free(next_bin);
	}


	if (result)
		print_sub("skip_binary ok\n", 1);
	else
		print_sub("skip_binary fail\n", 1);

	return result;
}

bool test_pieces() { 
	puts("\ntest_pieces():");

	cc_value_type val = 100;

	piece* pc = piece_create(val);
	bool c_result = pc->size == val;
	if (c_result)
		print_sub("create ok\n", 1);
	else
		print_sub("create fail\n", 1);

	piece_destroy(pc);
	print_sub("destroy ok\n", 1);

	size_t cap = 20;
	piece_list* list = piece_list_create(cap);
	bool lc_result = list->capacity == cap && list->size == 0;
	if (lc_result)
		print_sub("list create ok\n", 1);
	else
		print_sub("list create fail\n", 1);

	size_t num_ele = 7;
	cc_value_type values[] = {5, 2, 3, 88, 6, 52, 3};
	bool pb_result = true;
	for (size_t i = 0; i < num_ele; ++i) {
		piece* pc = piece_create(values[i]);
		piece_list_push_back(list, pc);
		pb_result |= list->size == i + 1;
	}
		
	if (pb_result)
		print_sub("push back ok\n", 1);
	else
		print_sub("push back fail\n", 1);	
	
	size_t new_size = cap + 1;
	for (size_t i = list->size; i <= new_size; ++i) {
		piece* pc = piece_create(10);
		piece_list_push_back(list, pc);
		pb_result |= list->size == i + 1;
	}
	bool cap_result = list->capacity > cap;
	if (cap_result)
		print_sub("realloc ok\n", 1);
	else
		print_sub("realloc fail\n", 1);	

	piece_list_destroy(list);

	list = piece_list_create(cap);
	for (size_t i = 0; i < num_ele; ++i) {
		piece* pc = piece_create(values[i]);
		piece_list_push_back(list, pc);
	}

	cc_value_type sorted[] = {88, 52, 6, 5, 3, 3, 2};
	piece_list_sort_desc(list);
	bool sort_result = true;
	for (size_t i = 0; i < num_ele; ++i)
		sort_result |= list->data[i]->size == sorted[i];

	if (sort_result)
		print_sub("sort ok\n", 1);
	else
		print_sub("sort fail\n", 1);


	piece_list_destroy(list);
	 
	return c_result && lc_result && pb_result && cap_result && sort_result;
}

bool test_containers() { 
	puts("\ntest_containers():");

	cc_value_type val = 100;

	container* ct = container_create(val);
	bool c_result = ct->capacity == val;
	if (c_result)
		print_sub("create ok\n", 1);
	else
		print_sub("create fail\n", 1);

	container_destroy(ct);
	print_sub("destroy ok\n", 1);

	size_t cap = 20;
	container_list* list = container_list_create(cap);
	bool lc_result = list->capacity == cap && list->size == 0;
	if (lc_result)
		print_sub("list create ok\n", 1);
	else
		print_sub("list create fail\n", 1);

	size_t num_ele = 7;
	cc_value_type values[] = { 5, 2, 3, 88, 6, 52, 3 };
	bool pb_result = true;
	for (size_t i = 0; i < num_ele; ++i) {
		container* ct = container_create(values[i]);
		container_list_push_back(list, ct);
		pb_result |= list->size == i + 1;
	}

	if (pb_result)
		print_sub("push back ok\n", 1);
	else
		print_sub("push back fail\n", 1);

	size_t new_size = cap + 1;
	for (size_t i = list->size; i <= new_size; ++i) {
		container* ct = container_create(10);
		container_list_push_back(list, ct);
		pb_result |= list->size == i + 1;
	}
	bool cap_result = list->capacity > cap;
	if (cap_result)
		print_sub("realloc ok\n", 1);
	else
		print_sub("realloc fail\n", 1);

	container_list_destroy(list);

	list = container_list_create(cap);
	for (size_t i = 0; i < num_ele; ++i) {
		container* ct = container_create(values[i]);
		container_list_push_back(list, ct);
	}

	cc_value_type sorted[] = { 2, 3, 3, 5, 6, 52, 88 };
	container_list_sort_asc(list);
	bool sort_result = true;
	for (size_t i = 0; i < num_ele; ++i)
		sort_result |= list->data[i]->capacity == sorted[i];

	if (sort_result)
		print_sub("sort ok\n", 1);
	else
		print_sub("sort fail\n", 1);


	container_list_destroy(list);

	return c_result && lc_result && pb_result && cap_result && sort_result;
}

bool test_piece_combos() {
	puts("\ntest_piece_combos():");

	unsigned key_num = 25;
	char* key = to_binary(key_num, 8);
	cc_value_type value = 512;

	piece_combo* combo = piece_combo_create(key, value);
	piece_combo_destroy(combo);
	print_sub("destroy ok\n", 1);

	size_t num_ele = 5;
	unsigned key_nums[] = {15, 2, 25, 100, 99};
	cc_value_type values[] = {888, 999, -663, 42, -12};

	bool result = true;
	for (size_t i = 0; i < num_ele; ++i) {
		char* key = to_binary(key_nums[i], 8);
		piece_combo* combo = piece_combo_create(key, values[i]);
		result |= strcmp(combo->binary, key) == 0 && combo->combo_size == values[i];
		piece_combo_destroy(combo);
	}

	if (result)
		print_sub("create ok\n", 1);
	else
		print_sub("create fail\n", 1);

	return result;
}

bool test_combo_size() { 
	puts("\ntest_combo_size():"); 

	piece_list* pieces = piece_factory(3, 30, 60, 40);
	if(pieces != NULL)
		print_sub("piece_factory ok\n", 1);
	else {
		print_sub("piece_factory fail\n", 1);
		return false;
	}

	piece_list_sort_desc(pieces);

	size_t num_ele = 7;
	char* combos[] = { "001", "010", "100", "101", "011", "110", "111" };
	cc_value_type loss = 0.0;
	cc_value_type expected[] = { 30.0, 40.0, 60.0, 90.0, 70.0, 100.0, 130.0 };	

	bool no_loss = true;
	for (size_t i = 0; i < num_ele; ++i) {
		no_loss |= cc_combo_size(combos[i], pieces, loss) == expected[i];
	}

	if (no_loss)
		print_sub("no loss ok\n", 1);
	else
		print_sub("no loss fail\n", 1);

	loss = 0.25;	
	cc_value_type expected_2[] = { 30.25, 40.25, 60.25, 90.5, 70.5, 100.5, 130.75 };
	bool with_loss = true;
	for (size_t i = 0; i < num_ele; ++i) {
		with_loss |= cc_combo_size(combos[i], pieces, loss) == expected[i];
	}
	if (no_loss)
		print_sub("with loss ok\n", 1);
	else
		print_sub("with loss fail\n", 1);

	piece_list_destroy(pieces);
	return no_loss && with_loss; 
}

bool test_filter_pieces() { 
	puts("\ntest_filter_pieces():"); 

	piece_list* pieces = piece_factory(3, 30, 20, 60);
	if (pieces != NULL)
		print_sub("piece_factory ok\n", 1);
	else {
		print_sub("piece_factory fail\n", 1);
		return false;
	}

	piece_list_sort_desc(pieces);

	size_t num_ele = 7;
	char* combos[] = { "001", "010", "100", "101", "011", "110", "111" };
	cc_value_type expected[][3] = {
		{20.0},
		{30.0},
		{60.0},
		{60.0, 20.0},
		{30.0, 20.0},
		{60.0, 30.0},
		{60.0, 30.0, 20.0}
	};

	size_t exp_sizes[] = {1, 1, 1, 2, 2, 2, 3};

	bool val_result = true;
	bool size_result = true;

	for (size_t i = 0; i < num_ele; ++i) {
		piece_list* filtered = cc_filter_pieces(combos[i], pieces);

		size_result |= filtered->size == exp_sizes[i];
		
		for (size_t j = 0; j < exp_sizes[i]; ++j)
			val_result |= filtered->data[j]->size == expected[j][i];

		piece_list_destroy_copy(filtered);
	}

	if (size_result)
		print_sub("list size ok\n", 1);
	else
		print_sub("list size fail\n", 1);

	if (val_result)
		print_sub("values ok\n", 1);
	else
		print_sub("values fail\n", 1);


	piece_list_destroy(pieces);
	return size_result && val_result; 
}

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