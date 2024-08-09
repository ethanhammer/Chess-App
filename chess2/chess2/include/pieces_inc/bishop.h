#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class bishop : public piece {

public:

    bishop(const std::string color);
    ~bishop() = default;


    std::vector<coord> calculatePotentialMovements(const coord &location) const override;

private:
    int validOffsets[4][2] = { {1, -1}, {-1, -1}, {-1, 1}, {1, 1} };
};


#endif // BISHOP_H
