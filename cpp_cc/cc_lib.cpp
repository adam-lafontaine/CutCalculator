#include <algorithm>
#include <sstream>
#include <iomanip>

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
cc_combo_key CC<T>::to_binary(int value, int num_bits) {

    std::stringstream ss;
    char bin_values[] = "01";
    int val = value;

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