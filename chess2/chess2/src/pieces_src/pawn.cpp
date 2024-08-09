#include "pawn.h"
#include "constants.h"

pawn::pawn(std::string color) : piece(color, "pawn") {};

std::vector<coord> pawn::calculatePotentialMovements(const coord &location) const {

    std::vector<coord> possibleMoves;

    int direction = (_color == "white") ? -1 : 1;
    int startRow = (_color == "white") ? 6 : 1;


    if (location.row + direction >= 0 && location.row + direction < boardSize) {
        possibleMoves.push_back(coord(location.row + direction, location.col));

        if (location.row == startRow) {
            possibleMoves.push_back(coord(location.row + (2 * direction), location.col));
        }

        if (location.col - 1 >= 0) {
            possibleMoves.push_back(coord(location.row + direction, location.col - 1)); // Capture left
        }
        if (location.col + 1 < boardSize) {
            possibleMoves.push_back(coord(location.row + direction, location.col + 1)); // Capture right
        }
    }

    return possibleMoves;
}


