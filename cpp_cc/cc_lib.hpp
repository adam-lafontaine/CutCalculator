#include <map>
#include <vector>
#include <memory>

template<typename T> using cc_list = std::vector<T>;

using cc_combo_key = std::string;

template<typename V> using cc_dict = std::map<cc_combo_key, V>;


struct PieceCombo;
struct Piece;
struct Container;
struct Result;

template<typename T>
using piece_combo_ptr = std::unique_ptr<PieceCombo<T>>;

template<typename T>
using piece_ptr = std::unique_ptr<Piece<T>>;

template<typename T>
using container_ptr = std::unique_ptr<Container<T>>;

template<typename T>
using result_ptr = std::unique_ptr<Result<T>>;



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
class CC {

private:
    cc_dict<piece_combo_ptr<T>> _piece_combos;
    cc_list<piece_ptr<T>> _pieces;
    cc_list<container_ptr<T>> _containers;
    cc_list<result_ptr<T>> _results;

    double _loss_per_piece;
    double _tolerance;

    // to_binary();
    // to_integer();
    // bool has_bit();
    // flip_bit();
    // bool has_common_bit();
    // next_binary()
    // skip_binary()
    // combo_size()
    // build_piece_combos()
    // filter_pieces()
    // best_match()
    // remove_combos()

public:
    CC();
    ~CC();

    // void set_inputs()
    // sort()




};