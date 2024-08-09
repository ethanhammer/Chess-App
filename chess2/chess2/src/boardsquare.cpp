#include "boardsquare.h"
#include <QUrl>
#include "board.h"

const int pieceSpacing = 10;

boardSquare::boardSquare(QWidget *parent, board &board, coord location) : QPushButton(parent), _board(board), _location(location) {
    setFocusPolicy(Qt::StrongFocus);
}

// Ensures the side and bottom are the same size. Adds a (pieceSpacing) padding to the sides of the icon image
void boardSquare::resizeEvent(QResizeEvent *event) {

    int sideLength = qMin(size().width(), size().height());
    resize(sideLength, sideLength);
    this->setIconSize(QSize(this->width()-pieceSpacing, this->height()-pieceSpacing));
}

// Changes highlight from current highlight by modifying stylesheet
void boardSquare::changeHighlight() {

    if (_highlighted == false) {
        this->setStyleSheet(this->styleSheet() + "border:4px solid red;");
        _highlighted=true;
    } else {
        QString currentStyleSheet = this->styleSheet();
        currentStyleSheet.replace("border:4px solid red;", "");
        this->setStyleSheet(currentStyleSheet);
        _highlighted=false;
    }
}

// Sets icon to nothing.
void boardSquare::resetIcon() {
    setIcon(QIcon());
    this->setIconSize(QSize(this->width(), this->height()));
}

// Updates icon to whatever the current piece is
void boardSquare::updateIcon() {
    if (_piece) {
         setIcon(QIcon(QString::fromUtf8(_piece->getImageLocation())));
        this->setIconSize(QSize(this->width()-pieceSpacing, this->height()-pieceSpacing));
    }

}

void boardSquare::mousePressEvent(QMouseEvent *event) {
    _board.recievePressed(_location);
}

// Methods move the pieces around
std::unique_ptr<piece> boardSquare::takePiece() {
    resetIcon();
    return std::move(_piece);
}

void boardSquare::receivePiece(std::unique_ptr<piece> piece) {
    _piece = std::move(piece);
    updateIcon();
}

