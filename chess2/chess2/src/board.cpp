#include "board.h"
#include "bishop.h"
#include "constants.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include <QMessageBox>

// Receives the clock and initializes the timers
void board::recieveClock(std::unique_ptr<Clock> clock) {
    _clock = std::move(clock);
    _clock->resetTimers();
}

// Receives the board squares and initializes the pieces
void board::recieveBoardSquares(std::vector<std::vector<boardSquare*>> boardSquares) {
    _boardSquares = std::move(boardSquares);
    createPieces();
}

// Ends the game and resets the timers
void board::endGame(const std::string &winner) {
    gameOn = false;
    _clock->resetTimers();
}

// Restarts the game, resets timers and pieces
void board::restartGame() {
    _clock->resetTimers();

    // Remove all pieces from the board
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (_boardSquares[i][j]->hasPiece()) {
                _boardSquares[i][j]->takePiece();
            }
        }
    }

    // Create and place new pieces
    createPieces();
    gameOn = true;
    clearHighlightTiles();
    clearSpotLightTile();
    _currentTurn = "white";
}

// Handles a press on a board square
void board::recievePressed(const coord& location) {

    if (!gameOn)
        return;

    // If a square is double clicked
    if (_spotLightTile == location) {
        clearHighlightTiles();
        clearSpotLightTile();
        return;
    }

    // Check if the clicked location is a highlighted tile
    for (coord& square : _highlightTiles) {
        if (square == location && isNotInCheck(_spotLightTile, location)) {
            executeMove(_spotLightTile, location);
            clearHighlightTiles();
            clearSpotLightTile();
            if (checkForMate()) {
                endGame(_currentTurn);
                return;
            }
            _clock->startTimer(_currentTurn);
            return;
        }
    }

    // Highlight the possible moves for the selected piece
    if (_boardSquares[location.row][location.col]->hasPiece()) {
        if (_boardSquares[location.row][location.col]->getPieceColor() == _currentTurn) {
            clearHighlightTiles();
            clearSpotLightTile();
            _spotLightTile = location;
            calculateHighlightTiles();
            doHighlights();
            _boardSquares[_spotLightTile.row][_spotLightTile.col]->changeHighlight();
            return;
        }
    }
}

// Checks if the current player is in checkmate
bool board::checkForMate() {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (_boardSquares[i][j]->hasPiece() && _boardSquares[i][j]->getPieceColor() == _currentTurn) {
                std::vector<coord> potentialMoves = _boardSquares[i][j]->getPieceMoves();
                std::vector<coord> realMoves;
                coord piecePosition(i, j);

                // Check the possible moves for each piece type
                if (_boardSquares[i][j]->getPieceName() == "pawn") {
                    checkPawnMoves(piecePosition, potentialMoves, realMoves);
                } else if (_boardSquares[i][j]->getPieceName() == "knight") {
                    checkKnightMoves(potentialMoves, realMoves);
                } else if (_boardSquares[i][j]->getPieceName() == "king") {
                    checkKingMoves(coord(i, j), potentialMoves, realMoves, true);
                } else {
                    checkGeneralMoves(piecePosition, potentialMoves, realMoves);
                }

                // If there is any move that gets the king out of check, it's not checkmate
                for (const coord& testSquare : realMoves) {
                    if (isNotInCheck(piecePosition, testSquare)) {
                        return false;
                    }
                }
            }
        }
    }
    return true; // No legal moves left, checkmate
}

// Checks if the move doesn't put the player in check
bool board::isNotInCheck(const coord& startingSquare, const coord& endingSquare) {

    std::vector<coord> dangerSquares;
    executeMove(startingSquare, endingSquare);
    dangerSquares = getAllInDangerSquares();

    for (const coord& dangerSquare : dangerSquares) {
        if (_boardSquares[dangerSquare.row][dangerSquare.col]->hasPiece()) {
            if (_boardSquares[dangerSquare.row][dangerSquare.col]->getPieceName() == "king" &&
                _boardSquares[dangerSquare.row][dangerSquare.col]->getPieceColor() != _currentTurn) {
                revertMove();
                return false;
            }
        }
    }
    revertMove();
    return true;
}

// Clears the highlighted tile
void board::clearSpotLightTile() {
    if (_spotLightTile.row != -1) {
        _boardSquares[_spotLightTile.row][_spotLightTile.col]->changeHighlight();
        _spotLightTile = coord();
    }
}

// Clears all highlighted tiles
void board::clearHighlightTiles() {
    for (coord& square : _highlightTiles) {
        _boardSquares[square.row][square.col]->changeHighlight();
    }
    _highlightTiles.clear();
}

// Calculates the possible moves for the currently selected piece
void board::calculateHighlightTiles() {
    std::vector<coord> potentialMoves = _boardSquares[_spotLightTile.row][_spotLightTile.col]->getPieceMoves();

    if (_boardSquares[_spotLightTile.row][_spotLightTile.col]->getPieceName() == "knight") {
        checkKnightMoves(potentialMoves, _highlightTiles);
    } else if (_boardSquares[_spotLightTile.row][_spotLightTile.col]->getPieceName() == "pawn") {
        checkPawnMoves(_spotLightTile, potentialMoves, _highlightTiles);
    } else if (_boardSquares[_spotLightTile.row][_spotLightTile.col]->getPieceName() == "king") {
        checkKingMoves(_spotLightTile, potentialMoves, _highlightTiles, true);
    } else {
        checkGeneralMoves(_spotLightTile, potentialMoves, _highlightTiles);
    }
}

// Refines the moves for a pawn, ensuring they are valid
void board::checkPawnMoves(const coord& pawnLocation, std::vector<coord>& allMoves, std::vector<coord>& refinedMoves) {
    for (coord& square : allMoves) {
        if (square.col != pawnLocation.col) {
            if (_boardSquares[square.row][square.col]->hasPiece() &&
                _boardSquares[square.row][square.col]->getPieceColor() != _currentTurn) {
                refinedMoves.push_back(square);
            }
        } else {
            if (!_boardSquares[square.row][square.col]->hasPiece() && canFindWayBack(square, pawnLocation)) {
                refinedMoves.push_back(square);
            }
        }
    }
}

// Refines the moves for a knight, ensuring they are valid
void board::checkKnightMoves(std::vector<coord>& allMoves, std::vector<coord>& refinedMoves) {
    for (coord& square : allMoves) {
        if (!_boardSquares[square.row][square.col]->hasPiece() ||
            _boardSquares[square.row][square.col]->getPieceColor() != _currentTurn) {
            refinedMoves.push_back(square);
        }
    }
}

// Gets all squares that are in danger for the current player
std::vector<coord> board::getAllInDangerSquares() {
    std::vector<coord> dangerSquares;

    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (_boardSquares[i][j]->hasPiece()) {
                if (_boardSquares[i][j]->getPieceColor() == _currentTurn) {
                    std::vector<coord> potentialMoves = _boardSquares[i][j]->getPieceMoves();
                    if (_boardSquares[i][j]->getPieceName() == "pawn") {
                        checkPawnMoves(coord(i, j), potentialMoves, dangerSquares);
                    } else if (_boardSquares[i][j]->getPieceName() == "knight") {
                        checkKnightMoves(potentialMoves, dangerSquares);
                    } else if (_boardSquares[i][j]->getPieceName() == "king") {
                        checkKingMoves(coord(i, j), potentialMoves, dangerSquares, false);
                    } else {
                        checkGeneralMoves(coord(i, j), potentialMoves, dangerSquares);
                    }
                }
            }
        }
    }

    return dangerSquares;
}

// Reverts the last move made
void board::revertMove() {
    _boardSquares[lastMove.oldLocation.row][lastMove.oldLocation.col]->receivePiece(
        _boardSquares[lastMove.newLocation.row][lastMove.newLocation.col]->takePiece()
        );
    if (lastMove.capturedPiece != nullptr) {
        _boardSquares[lastMove.newLocation.row][lastMove.newLocation.col]->receivePiece(std::move(lastMove.capturedPiece));
    }
    changeTurn();
}

// Handles king's possible moves and refines them based on whether the move leads to a check
void board::checkKingMoves(const coord& kingLocation, std::vector<coord>& allMoves, std::vector<coord>& refinedMoves, bool checkForCheck) {
    for (const coord& square : allMoves) {
        bool isEmptyOrOpponent = !_boardSquares[square.row][square.col]->hasPiece() ||
                                 _boardSquares[square.row][square.col]->getPieceColor() != _currentTurn;

        if (isEmptyOrOpponent) {
            // If checkForCheck is true, ensure the move is not leading to a square under attack
            if (!checkForCheck || isNotInCheck(kingLocation, square)) {
                refinedMoves.push_back(square);
            }
        }
    }
}

// Refines possible moves for non-special pieces by checking if the path is clear
void board::checkGeneralMoves(const coord& startingLocation, std::vector<coord>& allMoves, std::vector<coord>& refinedMoves) {
    for (coord& square : allMoves) {
        if (canFindWayBack(square, startingLocation)) {
            if (!_boardSquares[square.row][square.col]->hasPiece() ||
                _boardSquares[square.row][square.col]->getPieceColor() != _currentTurn) {
                refinedMoves.push_back(square);
            }
        }
    }
}

// Highlights the tiles that are currently in the highlight list
void board::doHighlights() {
    for (coord& square : _highlightTiles) {
        _boardSquares[square.row][square.col]->changeHighlight();
    }
}

// Checks if a piece can move from startingPoint to homePoint without being blocked
bool board::canFindWayBack(const coord &startingPoint, const coord &homePoint) {
    bool differentRow = (startingPoint.row != homePoint.row);
    bool differentCol = (startingPoint.col != homePoint.col);

    if (differentRow && differentCol) {
        // Diagonal movement
        int rowIncrement = (startingPoint.row > homePoint.row) ? -1 : 1;
        int colIncrement = (startingPoint.col > homePoint.col) ? -1 : 1;
        int currentRow = startingPoint.row + rowIncrement;
        int currentCol = startingPoint.col + colIncrement;

        while (currentRow != homePoint.row && currentCol != homePoint.col) {
            if (_boardSquares[currentRow][currentCol]->hasPiece()) {
                return false;
            }
            currentRow += rowIncrement;
            currentCol += colIncrement;
        }
    } else if (differentRow) {
        // Vertical movement
        int increment = (startingPoint.row > homePoint.row ? -1 : 1);
        int currentRow = startingPoint.row + increment;

        while (currentRow != homePoint.row) {
            if (_boardSquares[currentRow][homePoint.col]->hasPiece()) {
                return false;
            }
            currentRow += increment;
        }

    } else if (differentCol) {
        // Horizontal movement
        int increment = (startingPoint.col > homePoint.col ? -1 : 1);
        int currentCol = startingPoint.col + increment;

        while (currentCol != homePoint.col) {
            if (_boardSquares[homePoint.row][currentCol]->hasPiece()) {
                return false;
            }
            currentCol += increment;
        }
    }

    return true;
}

// Executes a move by updating the board state and changing the turn
void board::executeMove(const coord &oldLocation, const coord& newLocation) {
    move newLastMove;

    // Capture the piece at the new location if there is one
    if (_boardSquares[newLocation.row][newLocation.col]->hasPiece()) {
        newLastMove.capturedPiece = _boardSquares[newLocation.row][newLocation.col]->takePiece();
    }
    // Move the piece to the new location
    _boardSquares[newLocation.row][newLocation.col]->receivePiece(_boardSquares[oldLocation.row][oldLocation.col]->takePiece());

    newLastMove.newLocation = newLocation;
    newLastMove.oldLocation = oldLocation;

    lastMove = std::move(newLastMove); //record

    // Change the turn after the move
    changeTurn();
}

// Switches the current turn between white and black
void board::changeTurn() {
    _currentTurn = (_currentTurn == "white") ? "black" : "white";
}

// Creates and places pieces on the board at the start of the game
void board::createPieces() {
    // Lambda function to simplify the piece creation
    auto createPiece = [&](int row, int col, const std::string& color, const std::string& type) {
        if (type == "pawn") _boardSquares[row][col]->receivePiece(std::make_unique<pawn>(color));
        else if (type == "rook") _boardSquares[row][col]->receivePiece(std::make_unique<rook>(color));
        else if (type == "knight") _boardSquares[row][col]->receivePiece(std::make_unique<knight>(color));
        else if (type == "bishop") _boardSquares[row][col]->receivePiece(std::make_unique<bishop>(color));
        else if (type == "queen") _boardSquares[row][col]->receivePiece(std::make_unique<queen>(color));
        else if (type == "king") _boardSquares[row][col]->receivePiece(std::make_unique<king>(color));
    };

    // Place pawns on the board
    for (int col = 0; col < 8; ++col) {
        createPiece(6, col, "white", "pawn");
        createPiece(1, col, "black", "pawn");
    }

    // Place rooks
    createPiece(7, 0, "white", "rook");
    createPiece(7, 7, "white", "rook");
    createPiece(0, 0, "black", "rook");
    createPiece(0, 7, "black", "rook");

    // Place knights
    createPiece(7, 1, "white", "knight");
    createPiece(7, 6, "white", "knight");
    createPiece(0, 1, "black", "knight");
    createPiece(0, 6, "black", "knight");

    // Place bishops
    createPiece(7, 2, "white", "bishop");
    createPiece(7, 5, "white", "bishop");
    createPiece(0, 2, "black", "bishop");
    createPiece(0, 5, "black", "bishop");

    // Place queens
    createPiece(7, 3, "white", "queen");
    createPiece(0, 3, "black", "queen");

    // Place kings
    createPiece(7, 4, "white", "king");
    createPiece(0, 4, "black", "king");
}
