#ifndef KING_H
#define KING_H
#include "piece.h"

class king : public piece {

public:

    king(const std::string color);
    ~king() = default;


    std::vector<coord> calculatePotentialMovements(const coord& location) const override;

    bool getHasMoved() const { return hasMoved;}
    void setHasMoved() { hasMoved = true;}

private:

    int validOffsets[8][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {0, -1}, {-1, 0}, {0, 1} };
    bool hasMoved = false; // Will be used for castling

};
#endif // KING_H
