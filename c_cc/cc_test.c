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

	piece_list_sort_desc(list);

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

	cc_value_type cap = 0;

	container_list_sort_asc(list);

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

bool test_max_capacity() { 
	puts("\ntest_max_capacity():"); 

	container_list* c_lists[3];
	c_lists[0] = container_factory(3, 300.0, 200.0, 150.0);
	c_lists[1] = container_factory(4, 60.0, 40.0, 20.0, 80.0);
	c_lists[2] = container_factory(5, 10.5, 90.2, 62.4, 58.6, 25.6);

	size_t num_ele = 3;

	cc_value_type expected[] = { 300.0, 80.0, 90.2 };

	bool result = true;
	for (size_t i = 0; i < num_ele; ++i) {
		result |= cc_max_capacity(c_lists[i]) == expected[i];
		container_list_destroy(c_lists[i]);
	}

	if (result)
		print_sub("max capacity ok\n", 1);
	else
		print_sub("max capacity fail\n", 1);

	print_sub("Not Implemented\n", 1); 
	return result; 
}

bool test_build_piece_combos() { 
	puts("\ntest_build_piece_combos():"); 

	piece_list* pieces = piece_factory(3, 30.0, 20.0, 60.0);
	container_list* containers = container_factory(3, 300.0, 200.0, 150.0);

	cmap* piece_combos = cc_build_piece_combos(containers, pieces, 0);

	char* keys[] = { "001", "010", "011", "100", "101", "110", "111" };
	cc_value_type values[] = { 20, 30, 50, 60, 80, 90, 110 };

	size_t num_ele = 7;
	bool k_result = true;
	bool v_result = true;
	for (size_t i = 0; i < num_ele; ++i) {
		piece_combo* combo = cmap_get(piece_combos, keys[i]);
		k_result |= combo != NULL && strcmp(combo->binary, keys[i]) == 0;
		v_result |= combo != NULL && combo->combo_size == values[i];
	}

	if (k_result)
		print_sub("keys ok\n", 1);
	else
		print_sub("keys fail\n", 1);

	if (v_result)
		print_sub("values ok\n", 1);
	else
		print_sub("values fail\n", 1);
	
	cmap_destroy(piece_combos);
	piece_list_destroy(pieces);
	
	pieces = piece_factory(3, 90.0, 60.0, 180.0);
	piece_combos = cc_build_piece_combos(containers, pieces, 0);
	char* keys_2[] = { "001", "010", "011", "100", "101", "110", /*"111" too large*/ };
	cc_value_type values_2[] = { 60, 90, 150, 180, 240, 270, /*330 too large*/ };

	num_ele = 6;
	bool k_result_2 = true;
	bool v_result_2 = true;
	for (size_t i = 0; i < num_ele; ++i) {
		piece_combo* combo = cmap_get(piece_combos, keys[i]);
		k_result_2 |= combo != NULL && strcmp(combo->binary, keys_2[i]) == 0;
		v_result_2 |= combo != NULL && combo->combo_size == values_2[i];
	}

	if (k_result_2)
		print_sub("keys large ok\n", 1);
	else
		print_sub("keys large fail\n", 1);

	if (v_result_2)
		print_sub("values large ok\n", 1);
	else
		print_sub("values large fail\n", 1);

	bool max_result = cmap_get(piece_combos, "111") == NULL;
	if (max_result)
		print_sub("max ok\n", 1);
	else
		print_sub("max fail\n", 1);


	cmap_destroy(piece_combos);
	piece_list_destroy(pieces);
	container_list_destroy(containers);
	
	return k_result && v_result && k_result_2 && v_result_2 && max_result; 
}

bool test_best_match() { 
	puts("\ntest_best_match():"); 

	piece_list* pieces = piece_factory(5, 30.0, 20.0, 60.0, 40.0, 50.0);
	container_list* containers = container_factory(3, 85.0, 90.0, 110.0);

	cc_value_type loss = 0.25;
	cc_value_type tol = 0;

	cmap* piece_combos = cc_build_piece_combos(containers, pieces, loss);
	result* res = cc_best_match(containers, pieces, piece_combos, loss, tol);

	char* binary = "10001";
	cc_value_type combo_size = 80.5;
	cc_value_type pcs[] = { 20.0, 60.0 };
	cc_value_type container = 85.0;
	cc_value_type delta = 4.5;

	bool match_result = true;
	match_result &= strcmp(res->combo->binary, binary) == 0;
	match_result &= res->combo->combo_size == combo_size;
	match_result &= res->container->capacity == container;
	match_result &= res->delta == delta;

	size_t num_ele = 2;
	match_result &= res->pieces->size == num_ele;

	for (size_t i = 0; i < num_ele; ++i) {
		match_result &= res->pieces->data[i]->size == pcs[i];
	}
	
	

	if (match_result)
		print_sub(" ok\n", 1);
	else
		print_sub(" fail\n", 1);

	result_destroy(res);
	cmap_destroy(piece_combos);
	piece_list_destroy(pieces);
	container_list_destroy(containers);
	
	
	return match_result; 
}

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