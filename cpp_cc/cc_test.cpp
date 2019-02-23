#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
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
    string source[] = {"01110", "000", "1010110", "0000000", "0001000"};
    bool expected[] = {true, false, true, false, true};

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

string test_flip_bit() {
    print("\nTest flip_bit(char bit)");

    string success = "Pass";

    size_t num_ele = 2;
    char source[] = {'0', '1'};
    char expected[] = {'1', '0'};

    CC<int> my_cc;

    stringstream ss;

    for (size_t i = 0; i < num_ele; ++i) {
        auto src = source[i];
        auto exp = expected[i];
        auto res = my_cc.flip_bit(src);
        ss << "     bit = " << src << endl;
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

    vector<pair<string, string>> tests {
        {"has_bit", test_has_bit()},
        {"flip_bit", test_flip_bit()},
        {"to_binary()", test_to_binary()}
    };
    //tests["01 to_binary()"] = test_to_binary();

    print("\n");

    int width = 0;
    for(auto& test : tests){
        width = test.first.length() > width ? test.first.length() : width;
    }

    for(auto& test : tests) {
        cout << setfill(' ') << setw(width) << test.first << ": " << test.second << endl;
    }

    print("\n");
}