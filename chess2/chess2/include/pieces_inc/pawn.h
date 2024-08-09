#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class pawn : public piece {

public:

    pawn(const std::string color);
    ~pawn() = default;


    std::vector<coord> calculatePotentialMovements(const coord& location) const override;

};

#endif // PAWN_H
