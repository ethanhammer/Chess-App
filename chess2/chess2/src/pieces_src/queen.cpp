#include "queen.h"
#include "constants.h"

queen::queen(std::string color) : piece(color, "queen") {};

std::vector<coord> queen::calculatePotentialMovements(const coord &ocation) const {

    std::vector<coord> possibleMoves;

    for (int i = 0; i < 8; i++) {

        int dRow = validOffsets[i][0];
        int dCol = validOffsets[i][1];

        int targetRow = ocation.row + dRow;
        int targetCol = ocation.col + dCol;

        while (targetRow >= 0 && targetRow < boardSize && targetCol >= 0 && targetCol < boardSize) {

            coord newHighlight = {targetRow, targetCol};
            possibleMoves.push_back(newHighlight);

            targetRow += dRow;
            targetCol += dCol;
        }
    }

    return possibleMoves;
}
