#include <iostream>
#include <sstream>
#include <iomanip>
#include <tuple>
#include <string>
#include <algorithm>

#include "cc_lib.hpp"
#include "cc_test.hpp"

using namespace std;

void print(string const& msg) {
    cout << msg << '\n';
}

template<typename T>
void print(string const& label, std::initializer_list<T> const& list) {
    cout << label << ": [ ";
    auto last = list.size() - 1;    
     for(size_t i = 0; i <= last; ++i) {
        cout << *(list.begin() + i);
        if(i != last)
            cout <<", ";
    }
    cout << " ]" << endl;
}

template<typename T>
void print(string const& label, T value) {
    cout << label << ": " << value << endl;
}

template<typename T>
string vector_to_string(vector<T> const& list) {
    stringstream ss;
    ss << "[ ";
    auto last = list.size() - 1;    
     for(size_t i = 0; i <= last; ++i) {
        ss << *(list.begin() + i);
        if(i != last)
            ss <<", ";
    }
    ss << " ]";

    return ss.str();
}

template<typename T>
string list_to_string(initializer_list<T> const& list) {
    stringstream ss;
    ss << "[ ";
    auto last = list.size() - 1;    
     for(size_t i = 0; i <= last; ++i) {
        ss << *(list.begin() + i);
        if(i != last)
            ss <<", ";
    }
    ss << " ]";

    return ss.str();
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
        auto pc = std::make_shared<Piece<T>>();
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

     for(size_t i = 0; i < result.size() && i < expected.size(); ++i)
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

     for(size_t i = 0; i < result.size() && i < expected.size(); ++i)
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

//--------------------------------

string CCTest::test_combo_size() {
    print("\nTest combo_size(cc_combo_key const& binary)");

    string success = "Pass";

    auto pieces = piece_factory<double>({ 30.0, 60.0, 40.0 });
    vector<string> combos { "001", "010", "100", "101", "011", "110", "111" };
    vector<double> expected { 30.0, 40.0, 60.0, 90.0, 70.0, 100.0, 130.0 };

    CC<double> my_cc;
    my_cc.pieces(pieces);

    stringstream ss;

    print("pieces", { 30.0, 60.0, 40.0 });
    print("loss", my_cc.loss_per_piece());

     for(size_t i = 0; i < combos.size(); ++i) {
        auto combo = combos[i];
        auto res = my_cc.combo_size(combo);
        auto exp = expected[i];
        ss << combo << ":" << endl;
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
            success = "Fail";
    }

    print(ss.str());

    ss.str("");

    my_cc.loss_per_piece(0.25);

    vector<double> expected_2 { 30.25, 40.25, 60.25, 90.5, 70.5, 100.5, 130.75 };

    print("pieces", { 30.0, 60.0, 40.0 });
    print("loss", my_cc.loss_per_piece());

     for(size_t i = 0; i < combos.size(); ++i) {
        auto combo = combos[i];
        auto res = my_cc.combo_size(combo);
        auto exp = expected_2[i];
        ss << combo << ":" << endl;
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
            success = "Fail";
    }

    print(ss.str());

    return success;
}

//------------------------------

string CCTest::test_filter_pieces() {
    print("\nTest filter_pieces(cc_combo_key const& binary)");

    string success = "Pass";

    auto pieces = piece_factory<double>({ 30.0, 20.0, 60.0 });
    vector<string> combos { "001", "010", "100", "101", "011", "110", "111" };

    vector<vector<double>> expected_sizes {
        {20.0},
        {30.0},
        {60.0},
        {60.0, 20.0},
        {30.0, 20.0},
        {60.0, 30.0},
        {60.0, 30.0, 20.0}
    };

    CC<double> my_cc;
    my_cc.pieces(pieces);

    print("pieces", { 30.0, 20.0, 60.0 });

    stringstream ss;

     for(size_t i = 0; i < combos.size(); ++i) {
        auto combo = combos[i];
        auto combo_pieces = my_cc.filter_pieces(combo);

        // for comparison
        std::sort(combo_pieces.begin(), combo_pieces.end(), descending<double>);

        vector<double> sizes(combo_pieces.size());        
        std::transform(combo_pieces.begin(), combo_pieces.end(), sizes.begin(), 
            [](auto const& p) -> double { return p->size; });        

        auto expected = expected_sizes[i];
        auto res = vector_to_string(sizes);
        auto exp = vector_to_string(expected);
        ss << combo << ":" << endl;
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
            success = "Fail";
    }

    print(ss.str());

    return success;
}

//---------------------------

string CCTest::test_max_capacity() {
    print("\nTest max_capacity()");

    string success = "Pass";    

    vector<initializer_list<double>> capacities {
        { 300.0, 200.0, 150.0 },
        { 60.0, 40.0, 20.0, 80.0 },
        { 10.5, 90.2, 62.4, 58.6, 25.6 }
    };

    double loss = 0.5;
    vector<double> expected;

    CC<double> my_cc;

    stringstream ss;

    for(auto const& list : capacities) {
        auto containers = container_factory<double>(list);
        my_cc.containers(containers);
        my_cc.loss_per_piece(0.0);
        auto exp = max(list);
        auto res = my_cc.max_capacity();
        ss << "capacities: " << list_to_string(list) << endl;
        ss << " expected = " << exp << endl;
        ss << "   result = " << res << endl;
        if(exp != res)
            success = "Fail";
        
        my_cc.loss_per_piece(loss);
        exp += loss;
        res = my_cc.max_capacity();

        ss << "     loss: " << loss << endl;
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
            success = "Fail";

    }

    print(ss.str());    

    return success;
}

//------------------------

string CCTest::test_build_piece_combos() {
    print("\nTest build_piece_combos()");

    string success = "Pass";

    auto pieces = piece_factory<double>({ 30.0, 20.0, 60.0 });
    auto containers = container_factory<double>({ 300.0, 200.0, 150.0 });

    CC<double> my_cc;

    my_cc.pieces(pieces);
    my_cc.containers(containers);

    my_cc.build_piece_combos();

    vector<pair<string, double>> expected {
        { "001", 20.0 },
        { "010", 30.0 },
        { "011", 50.0 },
        { "100", 60.0 },
        { "101", 80.0 },
        { "110", 90.0 },
        { "111", 110.0 }
    };

    stringstream ss;

    auto result = &(my_cc._piece_combos);

    auto not_found = result->end();

    for(auto const& item : expected) {
        auto key = item.first;

        ss << "key: " << key;

        if(result->find(key) == not_found) {
            ss << " not found" << endl;
            success = "Fail";
            continue;
        }
        ss << endl;

        auto exp = item.second;
        auto res = (*result)[key]->combo_size;
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
            success = "Fail";
    }
    
    print(ss.str());

    result = nullptr;

    return success;
}

//------------------------------

string CCTest::test_best_match() {
    print("\nTest best_match()");

    string success = "Pass";

    auto pieces = piece_factory<double>({ 30.0, 20.0, 60.0, 40.0, 50.0 });
    auto containers = container_factory<double>({ 85.0, 90.0, 110.0 });

    CC<double> my_cc;

    my_cc.pieces(pieces);
    my_cc.containers(containers);
    my_cc.loss_per_piece(0.25);

    vector<pair<string, string>> expected {
        {"binary", "10001"},
        {"combo_size", list_to_string<double>({80.5})},
        {"pieces", list_to_string<double>({20.0, 60.0})},
        {"container", list_to_string({85.0})},
        {"delta", list_to_string<double>({4.5})}
    };

    my_cc.build_piece_combos();

    auto match = my_cc.best_match();
    
    vector<double> res_pieces(match->pieces.size());
    transform(match->pieces.begin(), match->pieces.end(), res_pieces.begin(),
    [](auto const& p) -> double { return p->size; });

    map<string, string> result {
        {"binary", match->binary},
        {"combo_size", list_to_string<double>({match->combo->combo_size})},
        {"pieces", vector_to_string(res_pieces)},
        {"container", list_to_string({match->container->capacity})},
        {"delta", list_to_string<double>({match->delta})}
    };

    stringstream ss;

    for(auto const& item : expected) {
        auto exp = item.second;
        auto res = result[item.first];
        ss << item.first << ":" << endl;
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
            success = "Fail";
    }
    
    print(ss.str());

    return success;
}

//-----------------------------

string CCTest::test_remove_combos() {
    print("\nTest remove_combos()");

    string success = "Pass";

    auto pieces = piece_factory<double>({ 30.0, 20.0, 60.0 });
    auto containers = container_factory<double>({ 300.0, 200.0, 150.0 });

    CC<double> my_cc;

    my_cc.pieces(pieces);
    my_cc.containers(containers);
    my_cc.loss_per_piece(0.0);
    my_cc.build_piece_combos();

    auto func_1 = [](auto const& item) -> string { 
        stringstream ss;
        ss << "{" << item.first << " : " << item.second->combo_size << "}";
        return ss.str();
        };

    auto func_2 = [](auto const& item) -> string { 
        stringstream ss;
        ss << "{" << item.first << " : " << item.second << "}";
        return ss.str();
        };

    vector<cc_combo_key> combos(my_cc._piece_combos.size());
    std::transform(my_cc._piece_combos.begin(), my_cc._piece_combos.end(), combos.begin(), func_1);

    auto binary = "010";

    vector<pair<string, double>> expected {
        {"001", 20.0},
        {"100", 60.0},
        {"101", 80.0}
    };

    vector<string> exp_str(expected.size());
    std::transform(expected.begin(), expected.end(), exp_str.begin(), func_2);

    stringstream ss;
    
    ss << "combos: " << vector_to_string<string>(combos) << endl;
    ss << "binary: " << binary << endl;

    my_cc.remove_combos(binary);

    vector<string> result(my_cc._piece_combos.size());
    std::transform(my_cc._piece_combos.begin(), my_cc._piece_combos.end(), result.begin(), func_1);

    auto exp = vector_to_string(exp_str);
    auto res = vector_to_string(result);

    ss << "expected: " << exp << endl;
    ss << "  result: " << res << endl;

    if(exp != res)
        success = "Fail";    

    print(ss.str());

    return success;
}

//-----------------------------------

string CCTest::test_sort() {
    print("\nTest sort()");

    string success = "Pass";

    auto pieces = piece_factory<double>({ 
        10.0, 10.0, 10.0, 
        48.0, 48.0, 48.0, 
        30.0, 30.0, 30.0
        });

    auto containers = container_factory<double>({ 
        100.0, 100.0, 100.0 , 100.0, 100.0,
        100.0, 100.0, 100.0 , 100.0, 100.0
        });

    vector<pair<initializer_list<double>, double>> expected { // pieces, delta
        { { 10.0, 30.0, 30.0, 30.0 }, 0.0 },
        { { 48.0, 48.0 }, 4.0 },
        { { 10.0, 10.0, 48.0 }, 32.0}
    };

    stringstream ss;

    CC<double> my_cc;

    ss <<"No loss per piece:" << endl;
    my_cc.pieces(pieces);
    my_cc.containers(containers);
    my_cc.loss_per_piece(0.0);

    auto result_dto = my_cc.sort();
    ss << result_dto.message << endl;
    if(!result_dto.success)
        success = "Fail";    

    // compare
    auto res_data = result_dto.data;
    auto exp_count = expected.size();
    auto res_count = res_data.size();
    ss << "expected count = " << exp_count << endl;
    ss << "  sorted count = " << res_count << endl;
    if(exp_count != res_count)
        success = "Fail";

    vector<double> piece_sizes;
    for(size_t i = 0; i < exp_count && i < res_count; ++i) {
        auto result = res_data[i];
        auto beg = result->pieces.begin();
        auto end = result->pieces.end();
        piece_sizes.clear();
        piece_sizes.resize(result->pieces.size());
        auto lambda = [](auto const& pc) -> double { return pc->size; };
        transform(beg, end, piece_sizes.begin(), lambda);
        
        ss << "pieces:" << endl;
        auto exp = list_to_string(expected[i].first);
        auto res = vector_to_string(piece_sizes);
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
            success = "Fail";

        ss << "delta:" <<endl;
        auto exp_delta = expected[i].second;
        auto res_delta = result->delta;
        ss << "expected = " << exp_delta << endl;
        ss << "  result = " << res_delta << endl;
        if(exp_delta != res_delta)
            success = "Fail";
    }

    pieces.clear();
    containers.clear();

    pieces = piece_factory<double>({ 
        10.0, 10.0, 10.0, 
        48.0, 48.0, 48.0, 
        30.0, 30.0, 30.0
        });

    containers = container_factory<double>({ 
        100.0, 100.0, 100.0 , 100.0, 100.0,
        100.0, 100.0, 100.0 , 100.0, 100.0
        });

    expected.clear();
    expected.push_back({ { 10.0, 10.0, 30.0, 48.0 }, 1.0 });
    expected.push_back({ { 48.0, 48.0 }, 3.5 });
    expected.push_back({ { 10.0, 30.0, 30.0 }, 29.25 });

    ss << "With loss per piece:" << endl;
    my_cc.pieces(pieces);
    my_cc.containers(containers);
    my_cc.loss_per_piece(0.25);

    result_dto = my_cc.sort();
    ss << result_dto.message << endl;
    if(!result_dto.success)
        success = "Fail";
    
    // compare
    res_data = result_dto.data;
    exp_count = expected.size();
    res_count = res_data.size();
    ss << "expected count = " << exp_count << endl;
    ss << "  sorted count = " << res_count << endl;
    if(exp_count != res_count)
        success = "Fail";
    
    for(size_t i = 0; i < exp_count && i < res_count; ++i) {
        auto result = res_data[i];
        auto beg = result->pieces.begin();
        auto end = result->pieces.end();
        piece_sizes.clear();
        piece_sizes.resize(result->pieces.size());
        auto lambda = [](auto const& pc) -> double { return pc->size; };
        transform(beg, end, piece_sizes.begin(), lambda);
        
        ss << "pieces:" << endl;
        auto exp = list_to_string(expected[i].first);
        auto res = vector_to_string(piece_sizes);
        ss << "expected = " << exp << endl;
        ss << "  result = " << res << endl;
        if(exp != res)
            success = "Fail";

        ss << "delta:" <<endl;
        auto exp_delta = expected[i].second;
        auto res_delta = result->delta;
        ss << "expected = " << exp_delta << endl;
        ss << "  result = " << res_delta << endl;
        if(exp_delta != res_delta)
            success = "Fail";
    }


    print(ss.str());

    return success;
}

// linux
// g++ -o run_tests cc_test.cpp cc_lib.cpp
// ./run_tests

