#include "bishop.h"
#include "constants.h"

bishop::bishop(std::string color) : piece(color, "bishop") {};

std::vector<coord> bishop::calculatePotentialMovements(const coord& location) const {

    std::vector<coord> possibleMoves;

    for (int i = 0; i < 4; i++) {

        int dRow = validOffsets[i][0];
        int dCol = validOffsets[i][1];

        int targetRow = location.row + dRow;
        int targetCol = location.col + dCol;

        while (targetRow >= 0 && targetRow < boardSize && targetCol >= 0 && targetCol < boardSize) {

            coord newHighlight = {targetRow, targetCol};
            possibleMoves.push_back(newHighlight);

            targetRow += dRow;
            targetCol += dCol;
        }
    }

    return possibleMoves;
}
