#include "piece.h"

piece::piece(std::string color, std::string name) : _color(color), _name(name) {}

std::string piece::getImageLocation() const {
    return std::string(":/resources/art/" + _color + _name + ".png");
}
