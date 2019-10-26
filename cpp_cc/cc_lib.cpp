#include <algorithm>
#include <iomanip>
#include <cmath>

#include "cc_lib.hpp"

// must declare used types here or include implementation in header
template class CC<int>;
template class CC<double>;



//-------------------------------------


bool has_bit(cc_combo_key const& binary) noexcept {
    return binary.find(cc_true) != std::string::npos;
}

//--------------------------------


cc_bit_type flip_bit(cc_bit_type const bit) noexcept {
    return bit == cc_false ? cc_true : cc_false;
}

//--------------------------------------


cc_combo_key to_binary(u_int_t value, unsigned const num_bits) noexcept {
    
    cc_bit_type const bin_values[] = {cc_false, cc_true};

    auto const min_bits = static_cast<unsigned>(log2(value)+1);

    cc_combo_key binary(std::max(num_bits, min_bits), cc_false);

    auto bin_idx = binary.size();

    while(value > 0) {
        auto const idx = value % 2;
        binary[--bin_idx] = bin_values[idx];
        value -= idx;
        value /= 2;
    }

    return binary;
}

//-------------------------------


u_int_t to_decimal(cc_combo_key const& binary) noexcept {
    u_int_t val = 0;
    int exp = 0;

    // this works too
    /*
    auto const cond_f = [&](auto const& bit){
        if(bit == cc_true)
            val += static_cast<u_int_t>(std::pow(2, exp));

        ++exp;
    };

    std::for_each(binary.rbegin(), binary.rend(), cond_f);
    */
    

    // this is shorter    
    for(auto it = binary.rbegin(); it != binary.rend(); ++it) {
        if(*it == cc_true)
            val += static_cast<u_int_t>(std::pow(2, exp));

        ++exp;
    }
    

    return val;
}

//------------------------

// AND operation
bool has_common_bit(cc_combo_key const& bin_1, cc_combo_key const& bin_2) noexcept {

    auto const last_1 = bin_1.size() - 1;
    auto const last_2 = bin_2.size() - 1;

    for(size_t i = 0; i <= last_1 && i <= last_2; ++i) {        
        if(bin_1[last_1 - i] == cc_true && bin_2[last_2 - i] == cc_true)
            return true;
    }

    return false;
}

//--------------------------------


cc_combo_key next_binary(cc_combo_key const& binary) noexcept {
/*
    auto const num_bits = binary.size();
	cc_combo_key next_bin = binary;

    // expresses intent
    for(int i = num_bits - 1; i >= 0; --i) { // auto breaks
        next_bin[i] = flip_bit(next_bin[i]);
        if(next_bin[i] == cc_true)
            break;
    }
*/

    cc_combo_key next_bin = binary; 
    
    // C style
	// set bits to true until a true bit is found
    for(int i = binary.size() - 1; i >= 0 && (next_bin[i] = flip_bit(next_bin[i])) != cc_true; --i)
		;
    
    return next_bin;
}

//----------------------------


cc_combo_key skip_binary(cc_combo_key const& binary) noexcept {

    auto const num_bits = binary.size();
	cc_combo_key next_bin = binary;

    next_bin[num_bits - 1] = cc_true;

	int i = num_bits - 2;
	while(i >= 0 && next_bin[i] != cc_true)
		next_bin[i--] = cc_true;

    return next_binary(next_bin);
}

//-------------------------------------

template<typename T>
void CC<T>::pieces(piece_list<T>& pieces) {

    _pieces.resize(pieces.size());
    _pieces.clear();

    for(auto& item : pieces){
        _pieces.push_back(std::move(item));
    }

    std::sort(_pieces.begin(), _pieces.end(), descending<T>);
}

//----------------------------------------

template<typename T>
void CC<T>::containers(container_list<T>& containers) {

    _containers.resize(containers.size());
    _containers.clear();

    for(auto& container : containers) {
        _containers.push_back(std::move(container));
    }

    std::sort(_containers.begin(), _containers.end(), ascending<T>);
}

//-------------------------------------

template<typename T>
void CC<T>::pieces(piece_list<T>&& pieces) {

	_pieces = std::move(pieces);

	std::sort(_pieces.begin(), _pieces.end(), descending<T>);
}

//----------------------------------------

template<typename T>
void CC<T>::containers(container_list<T>&& containers) {

	_containers = std::move(containers);

	std::sort(_containers.begin(), _containers.end(), ascending<T>);
}

//--------------------------------------

template<typename T>
T CC<T>::combo_size(cc_combo_key const& binary) const noexcept {

    T result = 0; // T is numeric
    auto const num_bits = binary.size();
    auto const num_pieces = _pieces.size();

    for(size_t i = 0; i < num_bits && i < num_pieces; ++i) {
        auto const bit = binary[num_bits - 1 - i];
        auto const size = _pieces[num_pieces - 1 - i]->size;
        if(bit == cc_true)
            result += size + _loss_per_piece;
    }

	return result;
}

//------------------------------------

template<typename T>
piece_list<T> CC<T>::filter_pieces(cc_combo_key const& binary) const noexcept {

    piece_list<T> list;
    auto const num_bits = binary.size();
    auto const num_pieces = _pieces.size();

    for(size_t i = 0; i < num_bits && i < num_pieces; ++i) {
        if(binary[num_bits - 1 - i] == cc_true)
            list.push_back(_pieces[num_pieces - 1 - i]);
    }

    return list;
}

//-----------------------------

template<typename T>
T CC<T>::max_capacity() const noexcept {

	if (_containers.empty())
		return 0;

    // last item because list is sorted
    return _containers[_containers.size() - 1]->capacity;
}

//------------------------------

template<typename T>
void CC<T>::build_piece_combos() noexcept {

    _piece_combos.clear();

    if(_containers.empty())
        return;

    auto binary = to_binary(1, _pieces.size());
    auto max_cap = max_capacity();

    while(has_bit(binary)) {
        auto const size = combo_size(binary);
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
result_ptr<T> CC<T>::best_match() noexcept {

    result_ptr<T> result = std::make_shared<Result<T>>();

    if(_containers.empty())
        return result;

    auto const max_cap = max_capacity();
    auto best_diff = max_cap;
    auto best_container_it = _containers.begin();

    for(auto it = _piece_combos.rbegin(); it != _piece_combos.rend(); ++it) {
        auto const binary = it->first;
        auto const combo = it->second;
        auto const size = combo->combo_size;

        for(auto c_it = _containers.begin(); c_it != _containers.end(); ++c_it) {          
            auto diff = (*c_it)->capacity - size;

            if(0 <= diff && diff < best_diff) {
                best_diff = diff;
                result->binary = binary;
				best_container_it = c_it;

                if(diff <= tolerance()) {
                    result->combo = combo;
                    result->pieces = filter_pieces(binary);
                    result->container = std::move(*best_container_it);
                    result->delta = diff;
                    _containers.erase(best_container_it);
                    
                    return result;
                }
            }
        }
    }    

    result->combo = _piece_combos[result->binary];
    result->pieces = filter_pieces(result->binary);
    result->container = std::move(*best_container_it);
    result->delta = best_diff;
    _containers.erase(best_container_it);

    return result;
}

//---------------------------

template<typename T>
void CC<T>::remove_combos(cc_combo_key const& binary) noexcept {

    bool has_max = !_containers.empty();
	T max_cap{};

    if(has_max)
        max_cap = max_capacity();

    auto const cond_f = [&](auto const& combo) -> bool {
       return has_common_bit(combo.first, binary) || 
        (has_max && combo.second->combo_size > max_cap);
    };

    // erase - remove idiom does not work for std::map    
    /*
    _piece_combos.erase(std::remove_if(_piece_combos.begin(), _piece_combos.end(), cond_f), _piece_combos.end());
    */

    
    auto it = _piece_combos.begin();
    auto const end = _piece_combos.end();
    while(it != end) {
        if(cond_f(*it))
            _piece_combos.erase(it++);
        else 
            ++it;

    }    

}

template<typename T>
CCSortDTO<T> CC<T>::sort() noexcept {

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