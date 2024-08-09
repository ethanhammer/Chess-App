#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class knight : public piece {

public:

    knight(const std::string color);
    ~knight() = default;


    std::vector<coord> calculatePotentialMovements(const coord& location) const override;

private:
    int validOffsets[8][2] = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };
};
#endif // KNIGHT_H
