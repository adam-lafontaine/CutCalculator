#include <algorithm>
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
    return binary.find(cc_true) != std::string::npos;
}

//--------------------------------


cc_bit_type flip_bit(cc_bit_type bit) {
    return bit == cc_false ? cc_true : cc_false;
}

//--------------------------------------


cc_combo_key to_binary(u_int_t value, unsigned num_bits) {
    
    cc_bit_type bin_values[] = {cc_false, cc_true};
    u_int_t val = value;

    int min_bits = (int)log2(value)+1;

    cc_combo_key binary(std::max((int)num_bits, min_bits), cc_false);

    int bin_idx = binary.size();

    while(val > 0) {
        auto idx = val % 2;
        --bin_idx;
        binary[bin_idx] = bin_values[idx];
        val -= idx;
        val /= 2;
    }

    return binary;
}

//-------------------------------


u_int_t to_decimal(cc_combo_key const& binary) {
    u_int_t val = 0;
    int exp = -1;
    for(auto it = binary.rbegin(); it != binary.rend(); ++it) {
        ++exp;
        if(*it == cc_true)
            val += (u_int_t)std::pow(2, exp);
    }

    return val;
}

//------------------------


bool has_common_bit(cc_combo_key const& bin_1, cc_combo_key const& bin_2) {

    auto last_1 = bin_1.size() - 1;
    auto last_2 = bin_2.size() - 1;

    for(int i = 0; i <= last_1 && i <= last_2; ++i) {        
        if(bin_1[last_1 - i] == cc_true && bin_2[last_2 - i] == cc_true)
            return true;
    }

    return false;
}

//--------------------------------


cc_combo_key next_binary(cc_combo_key const& binary) {

    size_t num_bits = binary.size();
	cc_combo_key next_bin = binary;

    for(int i = num_bits - 1; i >= 0; --i) {
        next_bin[i] = flip_bit(next_bin[i]);
        if(next_bin[i] == cc_true)
            break;
    }

    return next_bin;
}

//----------------------------


cc_combo_key skip_binary(cc_combo_key const& binary) {

    size_t num_bits = binary.size();
	cc_combo_key next_bin = binary;

    next_bin[num_bits - 1] = cc_true;

    for(int i = num_bits - 2; i >= 0; --i) {
        if(next_bin[i] == cc_true)
            break;
        else
            next_bin[i] = cc_true;
    }

    return next_binary(next_bin);
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
        if(bit == cc_true)
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
        if(bit == cc_true)
            result.push_back(_pieces[_pieces.size() - 1 - i]);
    }

    //std::sort(result.begin(), result.end(), descending<T>); // not necessary

    return result;
}

//-----------------------------

template<typename T>
T CC<T>::max_capacity() {

    // last item because list is sorted
    return _containers[_containers.size() - 1]->capacity + _loss_per_piece;
}

//------------------------------

template<typename T>
void CC<T>::build_piece_combos() {

    _piece_combos.clear();

    if(_containers.empty())
        return;

    auto binary = to_binary(1, _pieces.size());
    auto max_cap = max_capacity();

    while(has_bit(binary)) {
        auto size = combo_size(binary);
        if(size <= max_cap) {
            _piece_combos[binary] = std::make_shared<PieceCombo<T>>(binary, size);
            binary = next_binary(binary);
        }
        else
            binary = skip_binary(binary);
    }
}

//----------------------------------------

template<typename T>
result_ptr<T> CC<T>::best_match() {

    result_ptr<T> result = std::make_shared<Result<T>>();

    if(_containers.empty())
        return result;

    auto max_cap = max_capacity();
    auto best_diff = max_cap;
    auto container_it = _containers.begin();

    for(auto it = _piece_combos.rbegin(); it != _piece_combos.rend(); ++it) {
        auto binary = it->first;
        auto size = _piece_combos[binary]->combo_size;

        for(auto c_it = _containers.begin(); c_it != _containers.end(); ++c_it) {          
            auto diff = (*c_it)->capacity - size;

            if(0 <= diff && diff < best_diff) {
                best_diff = diff;
                result->binary = binary;
                container_it = c_it;

                if(diff <= _tolerance) {
                    result->combo = _piece_combos[binary];
                    result->pieces = filter_pieces(binary);
                    result->container = std::move(*container_it);
                    _containers.erase(container_it);
                    result->delta = diff;
                    return result;
                }
            }
        }
    }

    result->combo = _piece_combos[result->binary];
    result->pieces = filter_pieces(result->binary);
    result->container = std::move(*container_it);
    _containers.erase(container_it);
    result->delta = best_diff;

    return result;
}

//---------------------------

template<typename T>
void CC<T>::remove_combos(cc_combo_key const& binary) {

    bool has_max = !_containers.empty();
    T max_cap;

    if(has_max)
        max_cap = max_capacity();

    std::vector<cc_combo_key> combos(_piece_combos.size());
    std::transform(_piece_combos.begin(), _piece_combos.end(), combos.begin(),
        [](auto const& item) -> cc_combo_key { return item.first; });

    for(auto const& combo : combos) {
        if(has_common_bit(combo, binary) || (has_max && _piece_combos[combo]->combo_size > max_cap)) 
            _piece_combos.erase(combo);
    }

}

template<typename T>
CCSortDTO<T> CC<T>::sort() {

    build_piece_combos();

    _results.clear();

    while(!_containers.empty() && !_piece_combos.empty()) {
        auto match = best_match();
        remove_combos(match->binary);
        _results.push_back(match);
    }

    CCSortDTO<T> dto;

    dto.data = _results;

    if(_piece_combos.empty()) {
        dto.success = true;
        dto.message = "solution found";
    }
    else {
        dto.success = false;
        dto.message = "not enough containers";
    }

    return dto;
}