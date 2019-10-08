#include <map>
#include <vector>
#include <memory>

using cc_bit_type = char;
constexpr cc_bit_type cc_false = '0';
constexpr cc_bit_type cc_true = '1';

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
    T delta;

};

template<typename T>
struct CCSortDTO {
    public:

    result_list<T> data;
    bool success;
    std::string message;

};


template<typename T>
class CC {

    friend class CCTest;

private:    
    piece_list<T>               _pieces;
    container_list<T>           _containers;

    cc_dict<piece_combo_ptr<T>> _piece_combos;

    result_list<T>              _results;

    T _loss_per_piece = 0.0;
    T _tolerance = 0.0;
       
    T combo_size(cc_combo_key const& binary) const;
    piece_list<T> filter_pieces(cc_combo_key const& binary) const;
    T max_capacity() const;

    void build_piece_combos();
    
    result_ptr<T> best_match();
    void remove_combos(cc_combo_key const& binary);

public:
    CC() {}
    ~CC() {}

    CCSortDTO<T> sort();

    // setters
    void pieces(piece_list<T>& pieces);
    void containers(container_list<T>& containers);
    void loss_per_piece(T const& loss) { _loss_per_piece = loss; }
    void tolerance (T const& tolerance) { _tolerance = tolerance; }
    

    // getters
    piece_list<T> const& pieces() const { return _pieces; }
    container_list<T> const& containers() const { return _containers; }
    T const& loss_per_piece() const { return _loss_per_piece; }
    T const& tolerance() const { return _tolerance; }

};

// binary functions
bool has_bit(cc_combo_key const& binary);
cc_bit_type flip_bit(cc_bit_type bit);
cc_combo_key to_binary(u_int_t value, unsigned num_bits);
u_int_t to_decimal(cc_combo_key const& binary);    
bool has_common_bit(cc_combo_key const& bin_1, cc_combo_key const& bin_2);
cc_combo_key next_binary(cc_combo_key const& binary);
cc_combo_key skip_binary(cc_combo_key const& binary);