#include "king.h"
#include "constants.h"

king::king(std::string color) : piece(color, "king") {};

std::vector<coord> king::calculatePotentialMovements(const coord &location) const {

    std::vector<coord> possibleMoves;

    for (int i = 0; i < 8; i++) {

        int dRow = validOffsets[i][0];
        int dCol = validOffsets[i][1];

        int targetRow = location.row + dRow;
        int targetCol = location.col + dCol;

        if (targetRow >= 0 && targetRow < boardSize && targetCol >= 0 && targetCol < boardSize) {

            coord newHighlight = {targetRow, targetCol};
            possibleMoves.push_back(newHighlight);
        }
    }

    return possibleMoves;
}
