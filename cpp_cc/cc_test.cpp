#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <tuple>
#include <string>

#include "cc_lib.hpp"
#include "cc_test.hpp"

using namespace std;

void print(string const& msg) {
    cout << msg << endl;
}

//--------------------------------

string CCTest::test_has_bit() {
    print("\nTest has_bit(cc_combo_key const& binary)");

    string success = "Pass";

    size_t num_ele = 5;
    string source[] = {"01110", "000", "1010110", "0000000", "0001000"};
    bool expected[] = {true, false, true, false, true};
    
    stringstream ss;

    for (size_t i = 0; i < num_ele; ++i) {
        auto src = source[i];
        auto exp = expected[i] ? "true" : "false";
        auto res = has_bit(src) ? "true" : "false";
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

string CCTest::test_flip_bit() {
    print("\nTest flip_bit(char bit)");

    string success = "Pass";

    size_t num_ele = 2;
    char source[] = {'0', '1'};
    char expected[] = {'1', '0'};
    
    stringstream ss;

    for (size_t i = 0; i < num_ele; ++i) {
        auto src = source[i];
        auto exp = expected[i];
        auto res = flip_bit(src);
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

string CCTest::test_to_binary() {
    print("\nTest to_binary(int value, int num_bits)");

    string success = "Pass";

    vector<tuple<u_int_t, unsigned, string>> source { // value, num_bits, expected
        make_tuple(3205, 12, "110010000101"),
        make_tuple(55, 6, "110111"),
        make_tuple(55, 12, "000000110111"),
        make_tuple(3205, 5, "110010000101"),
        make_tuple(1, 12, "000000000001")      
    };
    
    stringstream ss;

    for(auto& item : source) {
        auto value = get<0>(item);
        auto num_bits = get<1>(item);
        auto exp = get<2>(item);
        auto res = to_binary(value, num_bits);
        ss << "value = " << value << ", num_bits = " << num_bits << endl;
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
                success = "Fail";
    }    

    print(ss.str());

    return success;
}

//---------------------------

string CCTest::test_to_decimal() {
    print("\nTest to_decimal(cc_combo_key const& binary)");

    string success = "Pass";

    vector<pair<string, u_int_t>> source {
        {"1011", 11},
        {"100011", 35},
        {"0000000", 0},
        {"1001001110001", 4721},
        {"00001011", 11},
        {"0000100011", 35},
        {"00001001001110001", 4721}
    };
    
    stringstream ss;

    for(auto& item : source) {
        auto bin = item.first;
        auto exp = item.second;
        auto res = to_decimal(bin);
        ss << "  binary = " << bin << endl;
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
            success = "Fail";
    }

    print(ss.str());    

    return success;

}

//----------------------------

string CCTest::test_has_common_bit() {
    print("\nTest has_common_bit(cc_combo_key const& bin_1, cc_combo_key const& bin_2)");

    string success = "Pass";
    
    vector<tuple<string, string, bool>> source {
        make_tuple("0", "0", false),
        make_tuple("0", "1", false),
        make_tuple("100110", "000100", true),
        make_tuple("0100110011", "0010", true),
        make_tuple("1001001", "0110110", false)
    };
    
    stringstream ss;

    for(auto& item : source) {
        auto bin_1 = get<0>(item);
        auto bin_2 = get<1>(item);
        auto exp = get<2>(item) ? "true" : "false";
        auto res = has_common_bit(bin_1, bin_2) ? "true" : "false";
        ss << "bin_1 = " << bin_1 << ", bin_2 = " << bin_2 << endl;
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
                success = "Fail";
    }    

    print(ss.str());

    return success;
}

//-----------------------------

string CCTest::test_next_binary() {
    print("\nTest next_binary(cc_combo_key const& binary)");

    string success = "Pass";

    vector<pair<string, string>> source {
        {"1011", "1100",},
        {"100011", "100100",},
        {"0000000", "0000001",},
        {"11111", "00000",},
        {"0010010", "0010011",}
    };
    
    stringstream ss;

    for(auto& item : source) {
        auto bin = item.first;
        auto exp = item.second;
        auto res = next_binary(bin);
        ss << "  binary = " << bin << endl;
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
            success = "Fail";
    }

    print(ss.str());    

    return success;
}

//-------------------------

string CCTest::test_skip_binary() {
    print("\nTest skip_binary(cc_combo_key const& binary)");

    string success = "Pass";

    vector<pair<string, string>> source {
        {"1100100", "1101000"},
        {"0010001000", "0010010000"},
        {"11111", "00000"}
    };
    
    stringstream ss;

    for(auto& item : source) {
        auto bin = item.first;
        auto exp = item.second;
        auto res = skip_binary(bin);
        ss << "  binary = " << bin << endl;
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
            success = "Fail";
    }

    print(ss.str());    

    return success;
}

//-------------------------------

template<typename T>
piece_list<T> piece_factory(std::initializer_list<T> sizes) {
    
    piece_list<T> vec;
    
    for(auto sz : sizes) {
        auto pc = std::make_unique<Piece<T>>();
        pc->size = sz;
        
        vec.push_back(std::move(pc));
    }

    return vec;
}

//-------------------------------

string CCTest::test_pieces() {
    print("\nTest pieces()");

    string success = "Pass";

    auto pieces = piece_factory<double>({ 30.0, 60.0, 20.0, 40.0 });

    CC<double> my_cc;
    my_cc.pieces(pieces);

    vector<double> expected { 60.0, 40.0, 30.0, 20.0 };
    vector<double> result;

    for(auto const& pc : my_cc.pieces())
        result.push_back(pc->size);

    
    vector<tuple<string, string, string>> comp;
    comp.push_back(make_tuple("num elements", to_string(expected.size()), to_string(result.size())));

    for(auto i = 0; i < result.size() && i < expected.size(); ++i)
        comp.push_back(make_tuple(to_string(i), to_string(expected[i]), to_string(result[i])));
    
    stringstream ss;

    for(auto const& item : comp) {
        auto label = get<0>(item);
        auto exp = get<1>(item);
        auto res = get<2>(item);
        ss << label << ":" << endl;
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
            success = "Fail";
    }

    print(ss.str());

    return success;
}

//-------------------------------

template<typename T>
container_list<T> container_factory(std::initializer_list<T> sizes) {
    
    container_list<T> vec;
    
    for(auto sz : sizes) {
        auto pc = std::make_unique<Container<T>>();
        pc->capacity = sz;
        
        vec.push_back(std::move(pc));
    }

    return vec;
}

//-------------------------------

string CCTest::test_containers() {
    print("\nTest containers()");

    string success = "Pass";

    auto containers = container_factory<double>({ 300.0, 200.0, 150.0 });

    CC<double> my_cc;
    my_cc.containers(containers);

    vector<double> expected { 150.0, 200.0, 300.0 };
    vector<double> result;

    for(auto const& pc : my_cc.containers())
        result.push_back(pc->capacity);

    
    vector<tuple<string, string, string>> comp;
    comp.push_back(make_tuple("num elements", to_string(expected.size()), to_string(result.size())));

    for(auto i = 0; i < result.size() && i < expected.size(); ++i)
        comp.push_back(make_tuple(to_string(i), to_string(expected[i]), to_string(result[i])));
    
    stringstream ss;

    for(auto const& item : comp) {
        auto label = get<0>(item);
        auto exp = get<1>(item);
        auto res = get<2>(item);
        ss << label << ":" << endl;
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
            success = "Fail";
    }

    print(ss.str());

    return success;
}

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

    CCTest tester;

    vector<pair<string, string>> tests {
        {"has_bit", tester.test_has_bit()},
        {"flip_bit", tester.test_flip_bit()},
        {"to_binary()", tester.test_to_binary()},
        {"to_decimal()", tester.test_to_decimal()},
        {"has_common_bit()", tester.test_has_common_bit()},
        {"next_binary()", tester.test_next_binary()},
        {"skip_binary()", tester.test_skip_binary()},
        {"pieces()", tester.test_pieces()},
        {"containers()", tester.test_containers()}
    };

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