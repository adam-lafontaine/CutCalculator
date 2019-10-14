#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#include "win32_leak_check.h"
#endif

//#define TEST_FOR_LEAKS

#include "cc_test.h"

#define MAX_TESTS 20
#define RESULT_BUFFER_SZ 50



void str_result(char* buffer, const char* name, const bool result);



int main(int argc, char** argv) {
#if defined(_WIN32) && defined(_DEBUG) && defined(TEST_FOR_LEAKS)
	int dbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;   // check block integrity
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF; // don't recycle memory
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;     // leak report on exit
	_CrtSetDbgFlag(dbgFlags);
#endif

	char results_buffer[MAX_TESTS][RESULT_BUFFER_SZ] = { 0 };

	str_result(results_buffer[0], "test_has_bit()", test_has_bit());
	str_result(results_buffer[1], "test_flip_bit()", test_flip_bit());
	str_result(results_buffer[2], "test_to_binary()", test_to_binary());
	str_result(results_buffer[3], "test_to_decimal()", test_to_decimal());
	str_result(results_buffer[4], "test_has_common_bit()", test_has_common_bit());
	str_result(results_buffer[5], "test_next_binary()", test_next_binary());
	str_result(results_buffer[6], "test_skip_binary()", test_skip_binary());
	str_result(results_buffer[7], "test_pieces()", test_pieces());
	str_result(results_buffer[8], "test_containers()", test_containers());
	str_result(results_buffer[9], "test_combo_size()", test_combo_size());
	str_result(results_buffer[10], "test_filter_pieces()", test_filter_pieces());
	str_result(results_buffer[11], "test_max_capacity()", test_max_capacity());
	str_result(results_buffer[12], "test_build_piece_combos()", test_build_piece_combos());
	str_result(results_buffer[13], "test_best_match()", test_best_match());
	str_result(results_buffer[14], "test_remove_combos()", test_remove_combos());
	str_result(results_buffer[15], "test_sort()", test_sort());
	

	unsigned width = 0;
	unsigned w;
	unsigned num_tests = 0;

	for (num_tests = 1; num_tests < MAX_TESTS && (w = strlen(results_buffer[num_tests-1])); ++num_tests) {
		if (w > width)
			width = w;
	}

	puts("\n\nTest Summary:\n");
	for (size_t i = 0; i < num_tests; ++i) {
		printf("% *s\n", width, results_buffer[i]);
	}
}

//==========================================




void str_result(char* buffer, const char* name, const bool result) {
	char pass_fail[10];

	if (result)
		sprintf_s(pass_fail, 10, "%s", "Pass");
	else
		sprintf_s(pass_fail, 10, "%s", "Fail");

	sprintf_s(buffer, RESULT_BUFFER_SZ, "%s: %s", name, pass_fail);
}



