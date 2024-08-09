#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <string>
#include <vector>
#include "boardsquare.h"
#include "clock.h"
#include "move.h"

class board {
public:

    board() = default;
    ~board() = default;

    void endGame(const std::string& winner); //called by clock to end game
    void restartGame(); //resets member variables and replaces pieces

    void recieveBoardSquares(std::vector<std::vector<boardSquare*>> boardSquares); //called by MainWindow. Gives access to the board squares to the board class.
    void recieveClock(std::unique_ptr<Clock> clock); //called by MainWindow. Gives access to the clock to the board class.

    void recievePressed(const coord& location); //whenever a square is pressed, it calls the board via this method.

private:

    std::unique_ptr<Clock> _clock; // controls clock and timing
    std::vector<std::vector<boardSquare*>> _boardSquares; //pointers to boardSquares
    std::vector<coord> _highlightTiles; //list of all the current movement options for the piece at the spotlight tile
    coord _spotLightTile = coord(); //last pressed tile
    move lastMove; //recording of the last move. Used to check for checks and mates.
    std::string _currentTurn = "white";
    bool gameOn = true;

    void clearSpotLightTile();
    bool canFindWayBack(const coord& startingPoint, const coord& homePoint); //checks if the potential moves recieved by the piece are able to reach back to the piece without an obstruction.
    void clearHighlightTiles();
    void calculateHighlightTiles(); //gathers potential moves from the piece at the tile pressed and ensures they are valid.
    void executeMove(const coord& oldLocation, const coord& newLocation); //moves piece from a to b. Also records the move as the last move.
    void doHighlights();
    void createPieces(); //creates all 32 pieces.
    void changeTurn();
    void revertMove();
    std::vector<coord> getAllInDangerSquares(); //coords of all the squares currently threatened by the enemy color.
    bool isNotInCheck(const coord& startingSquare, const coord& endingSquare); //checks a move to see if it would result in a check.
    bool checkForMate(); //checks if any friendly movement can cause isNotInCheck to return true;

    //refines potential moves taken from the piece based on rules and gamelogic. Called by calculateHighlightTile and getAllInDangerSquares.
    void checkPawnMoves(const coord& pawnLocation, std::vector<coord>& allMoves, std::vector<coord>& refinedMoves);
    void checkKnightMoves(std::vector<coord>& allMoves, std::vector<coord>& refinedMoves);
    void checkKingMoves(const coord& kingLocation, std::vector<coord>& allMoves, std::vector<coord>& refinedMoves, bool checkForCheck);
    void checkGeneralMoves(const coord& startingLocation, std::vector<coord>& allMoves, std::vector<coord>& refinedMoves); //queen, rook, bishop

};

#endif // BOARD_H
