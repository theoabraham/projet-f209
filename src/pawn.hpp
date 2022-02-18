#include <iostream>
#include "Position.hpp"

class Pawn {
    int _id;
	Position _position;
public:
    Pawn(int _id, Position _position);
    Position getPosition();
    void setPosition(Position newPosition);
};