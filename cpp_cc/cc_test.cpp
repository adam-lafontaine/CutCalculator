#include <iostream>
#include "cc_lib.hpp"

using namespace std;

void print(string const& msg) {
    cout << msg << endl;
}

string test_to_binary() {
    print("\nTest to_binary(int value, int num_bits)");

    string success = "Pass";
    

    return success;
}


int main() {

    map<string, string> tests;

    tests["01 to_binary()"] = test_to_binary();

    print("\n");

    for(auto& test : tests) {
        cout<< test.first << ": " << test.second << endl;
    }

    print("\n");
}