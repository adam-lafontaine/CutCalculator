#include <vector>
#include <iostream>
#include <iomanip>

#if defined(_WIN32)
#include "win32_leak_check.h"
#endif

//#define TEST_FOR_LEAKS

#include "cc_test.hpp"

using namespace std;

void print(string const& msg);


int main() {
#if defined(_WIN32) && defined(_DEBUG) && defined(TEST_FOR_LEAKS)
	int dbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;   // check block integrity
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF; // don't recycle memory
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;     // leak report on exit
	_CrtSetDbgFlag(dbgFlags);
#endif

	CCTest tester;

	vector<pair<string, string>> tests{
		{"has_bit", tester.test_has_bit()},
		{"flip_bit", tester.test_flip_bit()},
		{"to_binary()", tester.test_to_binary()},
		{"to_decimal()", tester.test_to_decimal()},
		{"has_common_bit()", tester.test_has_common_bit()},
		{"next_binary()", tester.test_next_binary()},
		{"skip_binary()", tester.test_skip_binary()},
		{"pieces()", tester.test_pieces()},
		{"containers()", tester.test_containers()},
		{"combo_size()", tester.test_combo_size()},
		{"filter_pieces()", tester.test_filter_pieces()},
		{"max_capacity()", tester.test_max_capacity()},
		{"build_piece_combos()", tester.test_build_piece_combos()},
		{"best_match()", tester.test_best_match()},
		{"remove_combos()", tester.test_remove_combos()},
		{"sort()", tester.test_sort()}
	};

	print("\n");

	size_t width = 0;
	for (auto& test : tests) {
		width = test.first.length() > width ? test.first.length() : width;
	}

	for (auto& test : tests) {
		cout << setfill(' ') << setw(width) << test.first << ": " << test.second << endl;
	}

	print("\n");
}

//==============================


