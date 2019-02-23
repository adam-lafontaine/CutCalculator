#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>

#include "cc_lib.hpp"

// must declare used types here or include implementation in header
template class CC<int>;

/*
template<typename T>
void CC<T>::set_inputs(piece_list<T> const& pieces, container_list<T> const& containers, T loss) {

    _results;

    _loss_per_piece = loss; // ?

    _pieces(pieces.begin(), pieces.end()); // sort by size desc
    _containers(containers.begin(), containers.end()); // sort by capacity asc

    std::sort(_pieces.begin(), _pieces.end(), descending);
    std::sort(_containers.begin(), _containers.end(), ascending);

    //build_piece_combos();

}
*/

//-------------------------------------

template<typename T>
bool CC<T>::has_bit(cc_combo_key const& binary) {
    return binary.find('1') != std::string::npos;
}

//--------------------------------

template<typename T>
char CC<T>::flip_bit(char bit) {
    return bit == '0' ? '1' : '0';
}

//--------------------------------------

template<typename T>
cc_combo_key CC<T>::to_binary(u_int_t value, unsigned num_bits) {

    std::stringstream ss;
    char bin_values[] = "01";
    u_int_t val = value;

    while(val > 0) {
        auto idx = val % 2;
        ss << bin_values[idx];
        val -= idx;
        val /= 2;
    }

    auto binary = ss.str();
    std::reverse(binary.begin(), binary.end());
    if(binary.length() < num_bits) {
        ss.str(""); // clear contents
        ss << std::setfill('0') << std::setw(num_bits) << binary;
        binary = ss.str();
    }

    return binary;
}

//-------------------------------

template<typename T>
u_int_t CC<T>::to_decimal(cc_combo_key const& binary) {
    u_int_t val = 0;
    int exp = -1;
    for(auto it = binary.rbegin(); it != binary.rend(); ++it) {
        ++exp;
        if(*it == '1')
            val += (u_int_t)std::pow(2, exp);

    }

    return val;
}

//------------------------

template<typename T>
bool CC<T>::has_common_bit(cc_combo_key const& bin_1, cc_combo_key const& bin_2) {

    auto last_1 = bin_1.length() - 1;
    auto last_2 = bin_2.length() - 1;

    for(size_t i = 0; i <= last_1 && i <= last_2; ++i) {        
        if(bin_1[last_1 - i] == '1' && bin_2[last_2 - i] == '1')
            return true;
    }

    return false;
}