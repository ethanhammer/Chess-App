#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

class queen : public piece {

public:

    queen(const std::string color);
    ~queen() = default;


    std::vector<coord> calculatePotentialMovements(const coord& ocation) const override;

private:
    int validOffsets[8][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {0, -1}, {-1, 0}, {0, 1} };
};
#endif // QUEEN_H
