#ifndef COORD_H
#define COORD_H


struct coord {

    // Defaut is set to out of bounds
    coord() : row(-1), col(-1) {};

    coord(int row, int col) : row(row), col(col) {};

    coord(const coord& other) : row(other.row), col(other.col) {}

    int row;
    int col;


    //operator overloads

    coord& operator=(const coord& other) {
        if (this != &other) {
            this->row = other.row;
            this->col = other.col;
        }
        return *this;
    }

    bool operator==(const coord& other) const {

        if (other.col == this->col && other.row == this->row) {
           return true;
        } else {
           return false;
        }

    }
};

#endif // COORD_H
