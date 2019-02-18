#include <map>
#include <vector>

template<typename T>
using cc_list = std::vector<T>;

using cc_combo_key = std::string;

template<typename V>
using cc_dict = std::map<cc_combo_key, V>;



//template<typename T>
struct PieceCombo {
    public:

    double combo_size;
    // other properties

};

//template<typename T>
struct Piece {
    public:

    double size;
    // other properties
};

struct Container {
    public:

    double capacity;

    // other properties
};

struct Result {
    public:

    cc_combo_key binary;
    PieceCombo combo;
    cc_list<Piece> pieces;
    Container container;
    double delta;

};



class CC {

private:
    cc_dict<PieceCombo> _piece_combos;
    cc_list<Piece> _pieces;
    cc_list<Container> _containers;
    cc_list<Result> _results;

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