

struct PieceCombo {    
    double combo_size;

    char binary[];

    // other properties
};

struct Piece {

    double size;

    // other properties
};

struct Container {

    double capacity;

    // other properties
};

/*
struct Result {    

    char binary[];
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

};*/