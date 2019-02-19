#include <algorithm>
#include <sstream>

#include "cc_lib.hpp"

template<typename T>
void CC<T>::set_inputs(piece_list<T> const& pieces, container_list<T> const& containers, T loss) {

    _results;

    _loss_per_piece = loss; // ?

    _pieces(pieces.begin(), pieces.end()); // sort by size desc
    _containers(containers.begin(), containers.end()); // sort by capacity asc

    std::sort(_pieces.begin(), _pieces.end(), descending);
    std::sort(_containers.begin(), _containers.end(), ascending);

    build_piece_combos();

}

//--------------------------------------

template<typename T>
cc_combo_key CC<T>::to_binary(int value, int num_bits) {

    std::stringstream result;
    char bin_values[] = "01";
    int val = value;

    while(val > 0) {
        auto idx = val % 2;
        result << bin_values[idx];
        val -= idx
        val /= 2


    }
    //stream << std::setfill('0') << std::setw(2) << value;

    return result.str();
}