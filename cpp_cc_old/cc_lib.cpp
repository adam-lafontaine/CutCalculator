#include <algorithm>
#include <iomanip>
#include <cmath>

#include "cc_lib.hpp"

// must declare used types here or include implementation in header
template class CC<int>;
template class CC<double>;



//-------------------------------------


bool has_bit(cc_combo_key const& binary) noexcept {
    return binary.find(CC_TRUE) != std::string::npos;
}

//--------------------------------


cc_bit_type flip_bit(cc_bit_type const bit) noexcept {
    return bit == CC_FALSE ? CC_TRUE : CC_FALSE;
}

//--------------------------------------


cc_combo_key to_binary(u_int_t value, unsigned const num_bits) noexcept {
    
    cc_bit_type const bin_values[] = {CC_FALSE, CC_TRUE};

    auto const min_bits = static_cast<unsigned>(log2(value)+1);

    cc_combo_key binary(std::max(num_bits, min_bits), CC_FALSE);

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
        if(bit == CC_TRUE)
            val += static_cast<u_int_t>(std::pow(2, exp));

        ++exp;
    };

    std::for_each(binary.rbegin(), binary.rend(), cond_f);
    */
    

    // this is shorter    
    for(auto it = binary.rbegin(); it != binary.rend(); ++it) {
        if(*it == CC_TRUE)
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
        if(bin_1[last_1 - i] == CC_TRUE && bin_2[last_2 - i] == CC_TRUE)
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
        if(next_bin[i] == CC_TRUE)
            break;
    }
*/

    cc_combo_key next_bin = binary; 
    
    // C style
	// set bits to true until a true bit is found
    for(int i = binary.size() - 1; i >= 0 && (next_bin[i] = flip_bit(next_bin[i])) != CC_TRUE; --i)
		;
    
    return next_bin;
}

//----------------------------


cc_combo_key skip_binary(cc_combo_key const& binary) noexcept {

    auto const num_bits = binary.size();
	cc_combo_key next_bin = binary;

    next_bin[num_bits - 1] = CC_TRUE;

	int i = num_bits - 2;
	while(i >= 0 && next_bin[i] != CC_TRUE)
		next_bin[i--] = CC_TRUE;

    return next_binary(next_bin);
}

//-------------------------------------

template<typename T>
void CC<T>::pieces(piece_list<T>& pieces) {

    pieces_.resize(pieces.size());
    pieces_.clear();

    for(auto& item : pieces){
        pieces_.push_back(std::move(item));
    }

    std::sort(pieces_.begin(), pieces_.end(), descending<T>);
}

//----------------------------------------

template<typename T>
void CC<T>::containers(container_list<T>& containers) {

    containers_.resize(containers.size());
    containers_.clear();

    for(auto& container : containers) {
        containers_.push_back(std::move(container));
    }

    std::sort(containers_.begin(), containers_.end(), ascending<T>);
}

//-------------------------------------

template<typename T>
void CC<T>::pieces(piece_list<T>&& pieces) {

	pieces_ = std::move(pieces);

	std::sort(pieces_.begin(), pieces_.end(), descending<T>);
}

//----------------------------------------

template<typename T>
void CC<T>::containers(container_list<T>&& containers) {

	containers_ = std::move(containers);

	std::sort(containers_.begin(), containers_.end(), ascending<T>);
}

//--------------------------------------

template<typename T>
T CC<T>::combo_size(cc_combo_key const& binary) const noexcept {

    T result = 0; // T is numeric
    auto const num_bits = binary.size();
    auto const num_pieces = pieces_.size();

    for(size_t i = 0; i < num_bits && i < num_pieces; ++i) {
        auto const bit = binary[num_bits - 1 - i];        
		if (bit == CC_TRUE) {
			auto const size = pieces_[num_pieces - 1 - i]->size;
			result += size + loss_per_piece_;
		}
            
    }

	return result;
}

//------------------------------------

template<typename T>
piece_list<T> CC<T>::filter_pieces(cc_combo_key const& binary) const noexcept {

    piece_list<T> list;
    auto const num_bits = binary.size();
    auto const num_pieces = pieces_.size();

    for(size_t i = 0; i < num_bits && i < num_pieces; ++i) {
        if(binary[num_bits - 1 - i] == CC_TRUE)
            list.push_back(pieces_[num_pieces - 1 - i]);
    }

    return list;
}

//-----------------------------

template<typename T>
T CC<T>::max_capacity() const noexcept {

	if (containers_.empty())
		return 0;

    // last item because list is sorted
    return containers_[containers_.size() - 1]->capacity;
}

//------------------------------

template<typename T>
void CC<T>::build_piece_combos() noexcept {

    piece_combos_.clear();

    if(containers_.empty())
        return;

    auto binary = to_binary(1, pieces_.size());
    auto max_cap = max_capacity();

    while(has_bit(binary)) {
        auto const size = combo_size(binary);
        if(size <= max_cap) {
            piece_combos_[binary] = std::make_shared<PieceCombo<T>>(binary, size);
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

    if(containers_.empty())
        return result;

    auto const max_cap = max_capacity();
    auto best_diff = max_cap;
    auto best_container_it = containers_.begin();

	auto const is_better = [&](auto diff) { return diff >= -1 * loss_per_piece_ && diff < best_diff; };

    for(auto it = piece_combos_.rbegin(); it != piece_combos_.rend(); ++it) {
        auto const binary = it->first;
        auto const combo = it->second;
        auto const size = combo->combo_size;

        for(auto c_it = containers_.begin(); c_it != containers_.end(); ++c_it) {          
            auto diff = (*c_it)->capacity - size;

			if (!is_better(diff))
				continue;

			best_diff = diff;
			result->binary = binary;
			best_container_it = c_it;

			if (diff > tolerance_)
				continue;

			result->combo = combo;
			result->pieces = filter_pieces(binary);
			result->container = std::move(*best_container_it);
			containers_.erase(best_container_it);
			result->delta = diff;

			return result;            
        }
    }    

    result->combo = piece_combos_[result->binary];
    result->pieces = filter_pieces(result->binary);
    result->container = std::move(*best_container_it);    
    containers_.erase(best_container_it);
	result->delta = best_diff;

    return result;
}

//---------------------------

template<typename T>
void CC<T>::remove_combos(cc_combo_key const& binary) noexcept {

    bool has_max = !containers_.empty();
	T max_cap{};

    if(has_max)
        max_cap = max_capacity();

    auto const cond_f = [&](auto const& combo) -> bool {
       return has_common_bit(combo.first, binary) || 
        (has_max && combo.second->combo_size > max_cap);
    };

    
    auto it = piece_combos_.begin();
    auto const end = piece_combos_.end();
    while(it != end) {
        if(cond_f(*it))
            piece_combos_.erase(it++);
        else 
            ++it;

    }    

}

template<typename T>
CCSortDTO<T> CC<T>::sort() noexcept {

    build_piece_combos();

    results_.clear();

    while(!containers_.empty() && !piece_combos_.empty()) {
        auto match = best_match();
        remove_combos(match->binary);
        results_.push_back(match);
    }

    CCSortDTO<T> dto;

    dto.data = results_;

    if(piece_combos_.empty()) {
        dto.success = true;
        dto.message = "solution found";
    }
    else {
        dto.success = false;
        dto.message = "not enough containers";
    }

    return dto;
}