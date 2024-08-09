#include "rook.h"
#include "constants.h"

rook::rook(std::string color) : piece(color, "rook") {};

std::vector<coord> rook::calculatePotentialMovements(const coord &location) const {

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
