#ifndef MOVE_H
#define MOVE_H
#include "coord.h"
#include "piece.h"
#include <memory>

struct move {

    coord oldLocation;
    coord newLocation;
    std::unique_ptr<piece> capturedPiece; //if a piece is taken, it temporarily holds that
};

#endif


