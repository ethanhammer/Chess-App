#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include "coord.h"

class piece {

public:

    virtual std::vector<coord> calculatePotentialMovements(const coord& location) const = 0;

    std::string getName() const { return _name; }
    std::string getColor() const { return _color; }

    std::string getImageLocation() const;

protected:

    piece(const std::string color, std::string name);

    std::string _color;

private:

    std::string _name;

};

#endif // PIECE_H
