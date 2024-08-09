#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include <QPushButton>
#include <memory>
#include "coord.h"
#include "piece.h"

class board;

class boardSquare : public QPushButton
{
    Q_OBJECT

public:
    // Constructor takes a reference to the board and its starting position
    boardSquare(QWidget *parent, board &board, coord location);

    // Change highlighted status
    void changeHighlight();

    bool isHighlighted() const { return _highlighted; }

    // Get potential moves for the piece on this square
    std::vector<coord> getPieceMoves() const { return _piece->calculatePotentialMovements(_location); }

    // Get piece details
    std::string getPieceName() const { return _piece->getName(); }
    std::string getPieceColor() const { return _piece->getColor(); }
    bool hasPiece() const { return _piece != nullptr; }

    // Piece management
    std::unique_ptr<piece> takePiece();
    void receivePiece(std::unique_ptr<piece> piece);

protected:

    // Override mouse press event
    void mousePressEvent(QMouseEvent *event) override;

    // Override resize event
    void resizeEvent(QResizeEvent *event) override;

private:

    // Member variables
    bool _highlighted = false;
    std::unique_ptr<piece> _piece; // Current piece held by the square
    coord _location;
    board& _board; // Refernce to the board

    // Reset the icon for the square
    void resetIcon();

    // Update the icon image
    void updateIcon();

};

#endif // BOARDSQUARE_H
