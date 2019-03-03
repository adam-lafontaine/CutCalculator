#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>

#include "cc_lib.hpp"

// must declare used types here or include implementation in header
template class CC<int>;
template class CC<double>;

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


bool has_bit(cc_combo_key const& binary) {
    return binary.find('1') != std::string::npos;
}

//--------------------------------


char flip_bit(char bit) {
    return bit == '0' ? '1' : '0';
}

//--------------------------------------


cc_combo_key to_binary(u_int_t value, unsigned num_bits) {

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


u_int_t to_decimal(cc_combo_key const& binary) {
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


bool has_common_bit(cc_combo_key const& bin_1, cc_combo_key const& bin_2) {

    auto last_1 = bin_1.length() - 1;
    auto last_2 = bin_2.length() - 1;

    for(size_t i = 0; i <= last_1 && i <= last_2; ++i) {        
        if(bin_1[last_1 - i] == '1' && bin_2[last_2 - i] == '1')
            return true;
    }

    return false;
}

//--------------------------------


cc_combo_key next_binary(cc_combo_key const& binary) {

    size_t num_bits = binary.size();
    char next_bin[num_bits + 1];
    next_bin[num_bits] = '\0';
    std::copy(binary.begin(), binary.end(), next_bin);

    for(size_t i = num_bits - 1; i >= 0; --i) {
        next_bin[i] = flip_bit(next_bin[i]);
        if(next_bin[i] == '1')
            break;
    }

    return std::string(next_bin);
}

//----------------------------


cc_combo_key skip_binary(cc_combo_key const& binary) {

    size_t num_bits = binary.size();
    char next_bin[num_bits + 1];
    next_bin[num_bits] = '\0';
    std::copy(binary.begin(), binary.end(), next_bin);

    next_bin[num_bits - 1] = '1';

    for(size_t i = num_bits - 2; i >= 0; --i) {        
        if(next_bin[i] == '1')
            break;
        else
            next_bin[i] = '1';       
    }

    return next_binary(std::string(next_bin));
}

//-------------------------------------

template<typename T>
void CC<T>::pieces(piece_list<T>& pieces) {

    _pieces.clear();

    for(auto it = pieces.begin(); it != pieces.end(); ++it)
        _pieces.push_back(std::move(*it));

    std::sort(_pieces.begin(), _pieces.end(), descending<T>);
}

//----------------------------------------

template<typename T>
void CC<T>::containers(container_list<T>& containers) {

    _containers.clear();

    for(auto it = containers.begin(); it != containers.end(); ++it)
        _containers.push_back(std::move(*it));

    std::sort(_containers.begin(), _containers.end(), ascending<T>);

}

//--------------------------------------

template<typename T>
T CC<T>::combo_size(cc_combo_key const& binary) {

    T result;

    for(auto i = 0; i < _pieces.size() && i < binary.size(); ++i) {
        auto bit = binary[binary.size() - 1 - i];
        auto size = _pieces[_pieces.size() - 1 - i]->size;
        if(bit == '1')
            result += size + _loss_per_piece;
    }

    return result;
}

//------------------------------------

template<typename T>
piece_list<T> CC<T>::filter_pieces(cc_combo_key const& binary) {

    piece_list<T> result;
    for(auto i = 0; i < binary.size() && i < _pieces.size(); ++i) {
        auto bit = binary[binary.size() - 1 - i];        
        if(bit == '1')
            result.push_back(_pieces[_pieces.size() - 1 - i]);
    }

    //std::sort(result.begin(), result.end(), descending<T>); // not necessary

    return result;
}

//-----------------------------

template<typename T>
T CC<T>::max_capacity() {

    //if(_containers.empty())
    //    return ?? T.zero ??;

    // last item as list is sorted
    return _containers[_containers.size() - 1]->capacity + _loss_per_piece;
}

//------------------------------

template<typename T>
void CC<T>::build_piece_combos() {

    if(_containers.empty())
        return;

    auto binary = to_binary(1, _pieces.size());
    auto max_cap = max_capacity();

    while(has_bit(binary)) {
        auto size = combo_size(binary);
        if(size <= max_cap) {
            _piece_combos[binary] = std::make_unique<PieceCombo<T>>(binary, size);
            binary = next_binary(binary);
        }
        else
            binary = skip_binary(binary);
    }

}