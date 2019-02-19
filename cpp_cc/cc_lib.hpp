#include <map>
#include <vector>
#include <memory>

using cc_combo_key = std::string;

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

    cc_dict<piece_combo_ptr<T>> _piece_combos;
    piece_list _pieces;
    container_list _containers;
    result_list _results;

    T _loss_per_piece;
    T _tolerance;

    cc_combo_key to_binary(int value, int num_bits);
    // to_integer();
    // bool has_bit();
    // flip_bit();
    // bool has_common_bit();
    // next_binary()
    // skip_binary()
    // combo_size()
    void build_piece_combos();
    // filter_pieces()
    // best_match()
    // remove_combos()

public:
    CC() {}
    ~CC();

    void set_inputs(piece_list<T> const& pieces, container_list<T> const& containers, T loss);
    void sort();




};