//
// Created by Mark Dimitrov on 15/02/2022.
//

#include "Piece.hpp"

Wall::Wall(std::vector<Position> occupiedCells):positions{occupiedCells} {
}

std::vector<Position> Wall::getPos() {
    return positions;
}
