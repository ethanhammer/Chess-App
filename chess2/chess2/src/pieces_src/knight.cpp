#include "knight.h"


knight::knight(std::string color) : piece(color, "knight") {};

std::vector<coord> knight::calculatePotentialMovements(const coord &location) const {

    std::vector<coord> possibleMoves;

    for (int i = 0; i < 8; i++) {
        int targetRow = location.row+validOffsets[i][0];
        int targetCol = location.col+validOffsets[i][1];
        if (targetRow < 8 && targetRow > -1 && targetCol < 8 && targetCol > -1) {
            possibleMoves.push_back(coord(targetRow, targetCol));
        }
    }

    return possibleMoves;
}
