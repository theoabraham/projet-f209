//
// Created by Mark Dimitrov on 15/02/2022.
//
#pragma once 

//#include "Player.h"
#include "Position.hpp"
#include <vector>



class Piece {

};

class Wall : public Piece{
private:
    std::vector<Position> positions;
public:
    Wall(std::vector<Position> occupiedCells);
    std::vector<Position> getPos();
};

class Pawn: public Piece{
}; 