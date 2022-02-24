//
// Created by Mark Dimitrov on 15/02/2022.
//


#ifndef PIECE_HPP
#define PIECE_HPP

#include "Position.hpp"
//#include "Player.hpp"
#include <memory>
#include <vector>
#include <iostream>

class Piece {

};


class Wall : public Piece{
private:
    std::vector<Position> positions;
public:
    std::vector<Position> getPos();
};

class Pawn : public Piece{
    Position position;

public: 
    //Pawn(Position posistion = {4,0}): position{position}{}
    //Ecrire construction w\ Piece
    //Pawn(){};
    Pawn(Position initialPos);
    Position getPos(){return position;}
    void setPos(Position pos) {position = pos;}
}; 

#endif 