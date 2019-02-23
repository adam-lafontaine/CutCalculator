#include <iostream>
#include <sstream>
#include <vector>
#include "cc_lib.hpp"

using namespace std;

void print(string const& msg) {
    cout << msg << endl;
}

//--------------------------------

string test_has_bit() {
    print("\nTest has_bit(cc_combo_key const& binary)");

    string success = "Pass";

    size_t num_ele = 5;
    vector<string> source{"01110", "000", "1010110", "0000000", "0001000"};
    vector<bool> expected{true, false, true, false, true};

    CC<int> my_cc;

    stringstream ss;

    for (size_t i = 0; i < num_ele; ++i) {
        auto src = source[i];
        auto exp = expected[i] ? "true" : "false";
        auto res = my_cc.has_bit(src) ? "true" : "false";
        ss << "  binary = " << src << endl;
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
            success = "Fail";
    }

    print(ss.str());    

    return success;
}

//-----------------------------

string test_to_binary() {
    print("\nTest to_binary(int value, int num_bits)");

    string success = "Pass";
    

    return success;
}

//-----------------------------

/*

string test_my_func() {
    print("\nTest my_func(int value, int num_bits)");

    string success = "Pass";
    

    return success;
}

 */

// g++ -o run_tests cc_test.cpp cc_lib.cpp
// ./run_tests

int main() {

    map<string, string> tests;

    tests["01 has_bit()"] = test_has_bit();

    //tests["01 to_binary()"] = test_to_binary();

    print("\n");

    for(auto& test : tests) {
        cout<< test.first << ": " << test.second << endl;
    }

    print("\n");
}