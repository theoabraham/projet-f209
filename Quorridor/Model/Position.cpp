//
// Created by Mark Dimitrov on 15/02/2022.
//

#include "Position.hpp"

Position::Position(std::string pos): Position(int(pos[0])-97, int(pos[1])-48){
};

Position::Position(int x, int y):x{x},y{y} {
}

bool Position::operator==(const Position& other) const {
    return (x == other.x and y == other.y);
}

