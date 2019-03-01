#include <map>
#include <vector>
#include <memory>

using cc_combo_key = std::string;
using u_int_t = unsigned long long;

template<typename T> using cc_list = std::vector<T>;
template<typename V> using cc_dict = std::map<cc_combo_key, V>;

template<typename T> struct PieceCombo;
template<typename T> struct Piece;
template<typename T> struct Container;
template<typename T> struct Result;

template<typename T> using piece_combo_ptr = std::unique_ptr<PieceCombo<T>>;
template<typename T> using piece_ptr = std::unique_ptr<Piece<T>>;
template<typename T> using container_ptr = std::unique_ptr<Container<T>>;
template<typename T> using result_ptr = std::unique_ptr<Result<T>>;

template<typename T> using piece_list = cc_list<piece_ptr<T>>;
template<typename T> using container_list = cc_list<container_ptr<T>>;
template<typename T> using result_list = cc_list<result_ptr<T>>;




template<typename T>
struct PieceCombo {
    public:

    T combo_size;
    // other properties

};

template<typename T>
struct Piece {
    public:

    T size;
    // other properties
};

template<typename T> inline
bool descending(piece_ptr<T> const& lhs, piece_ptr<T> const& rhs) { return lhs->size > rhs->size; }

template<typename T>
struct Container {
    public:

    T capacity;

    // other properties
};

template<typename T> inline
bool ascending(container_ptr<T> const& lhs, container_ptr<T> const& rhs) { return lhs->capacity < rhs->capacity; }

template<typename T>
struct Result {
    public:

    cc_combo_key binary;
    piece_combo_ptr<T> combo;
    cc_list<piece_ptr<T>> pieces;
    container_ptr<T> container;
    T delta;

};

template<typename T>
struct CCSortDTO {
    public:

    cc_list<result_ptr<T>> data;
    bool success;
    std::string message;

};


template<typename T>
class CC {

private:    
    piece_list<T>               _pieces;
    container_list<T>           _containers;

    cc_dict<piece_combo_ptr<T>> _piece_combos;
    result_list<T>              _results;

    T _loss_per_piece;
    T _tolerance;
       
    // combo_size()
    // void build_piece_combos();
    // filter_pieces()
    // best_match()
    // remove_combos()

public:
    CC() {}
    ~CC() {}

    //void sort();

    // setters
    void pieces(piece_list<T>& pieces);
    void containers(container_list<T>& containers);
    

    // getters
    piece_list<T> const& pieces() { return _pieces; }
    container_list<T> const& containers() { return _containers; }



    


};

// binary functions
bool has_bit(cc_combo_key const& binary);
char flip_bit(char bit);
cc_combo_key to_binary(u_int_t value, unsigned num_bits);
u_int_t to_decimal(cc_combo_key const& binary);    
bool has_common_bit(cc_combo_key const& bin_1, cc_combo_key const& bin_2);
cc_combo_key next_binary(cc_combo_key const& binary);
cc_combo_key skip_binary(cc_combo_key const& binary);