#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class rook : public piece {

public:

    rook(const std::string color);
    ~rook() = default;


    std::vector<coord> calculatePotentialMovements(const coord& location) const override;

    bool getHasMoved() const { return hasMoved;}
    void setHasMoved() { hasMoved = true;}

private:

    int validOffsets[4][2] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };

    bool hasMoved = false;
};
#endif // ROOK_H
