#include <map>
#include <vector>
#include <memory>
#include <algorithm>

using cc_bit_type = char;
constexpr cc_bit_type CC_FALSE = '0';
constexpr cc_bit_type CC_TRUE = '1';

//using cc_combo_key = std::string;
using cc_combo_key = std::basic_string<cc_bit_type>;
using combo_list = std::vector<std::unique_ptr<cc_combo_key>>;
using u_int_t = unsigned long long;

//template<typename T> using cc_list = std::vector<T>;
template<typename V> using cc_dict = std::map<cc_combo_key, V>;

template<typename T> struct PieceCombo;
template<typename T> struct Piece;
template<typename T> struct Container;
template<typename T> struct Result;

template<typename T> using piece_combo_ptr = std::shared_ptr<PieceCombo<T>>;
template<typename T> using piece_ptr = std::shared_ptr<Piece<T>>;
template<typename T> using container_ptr = std::unique_ptr<Container<T>>;
template<typename T> using result_ptr = std::shared_ptr<Result<T>>;

template<typename T> using piece_list = std::vector<piece_ptr<T>>;
template<typename T> using container_list = std::vector<container_ptr<T>>;
template<typename T> using result_list = std::vector<result_ptr<T>>;


template<typename T>
struct PieceCombo {
    public:

    PieceCombo(cc_combo_key const& bin, T const& sz) {
        binary = bin;
        combo_size = sz;
    }

    T combo_size;
    cc_combo_key binary;
    // other properties

};

template<typename T>
struct Piece {
    public:

    T size;
    // other properties
};

template<typename T> inline
bool descending(piece_ptr<T> const lhs, piece_ptr<T> const rhs) { return lhs->size > rhs->size; }

template<typename T> inline
bool ascending(container_ptr<T> const& lhs, container_ptr<T> const& rhs) { return lhs->capacity < rhs->capacity; }

template<typename T>
struct Container {
    public:

    T capacity;

    // other properties
};

template<typename T>
struct Result {
    public:

    cc_combo_key binary;
    piece_combo_ptr<T> combo;
    piece_list<T> pieces;
    container_ptr<T> container;
	T delta{};

};

template<typename T>
struct CCSortDTO {
    public:

    result_list<T> data;
    bool success = false;
    std::string message;

};


template<typename T>
class CC {

    friend class CCTest;

private:    
    piece_list<T>               pieces_;
    container_list<T>           containers_;

    cc_dict<piece_combo_ptr<T>> piece_combos_;

    result_list<T>              results_;

	T loss_per_piece_{};
	T tolerance_{};
       
    T combo_size(cc_combo_key const& binary) const noexcept;
    piece_list<T> filter_pieces(cc_combo_key const& binary) const noexcept;
    T max_capacity() const noexcept;

    void build_piece_combos() noexcept;
    
    result_ptr<T> best_match() noexcept;
    void remove_combos(cc_combo_key const& binary) noexcept;

public:
    CC() {}

    CCSortDTO<T> sort() noexcept;

    // setters
    void pieces(piece_list<T>& pieces);
    void containers(container_list<T>& containers);
	void pieces(piece_list<T>&& pieces);
	void containers(container_list<T>&& containers);
    void loss_per_piece(T const& loss) noexcept { loss_per_piece_ = loss; }
    void tolerance (T const& tolerance) noexcept { tolerance_ = tolerance; }
    

    // getters
    piece_list<T> const& pieces() const { return pieces_; }
    container_list<T> const& containers() const { return containers_; }
    T const& loss_per_piece() const { return loss_per_piece_; }
    T const& tolerance() const { return std::max(tolerance_, loss_per_piece_); }

};

// binary functions
bool has_bit(cc_combo_key const& binary) noexcept;
cc_bit_type flip_bit(cc_bit_type bit) noexcept;
cc_combo_key to_binary(u_int_t value, unsigned num_bits) noexcept;
u_int_t to_decimal(cc_combo_key const& binary) noexcept;
bool has_common_bit(cc_combo_key const& bin_1, cc_combo_key const& bin_2) noexcept;
cc_combo_key next_binary(cc_combo_key const& binary) noexcept;
cc_combo_key skip_binary(cc_combo_key const& binary) noexcept;