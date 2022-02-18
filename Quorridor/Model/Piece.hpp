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
    Wall();
    std::vector<Position> getPos();
};

class Pawn : public Piece{
    //Position position;  
    //std::shared_ptr<Player> player = std::shared_ptr<Player>(new Player());

public: 
    //Pawn(Position posistion = {4,0}): position{position}{}
    //Ecrire construction w\ Piece
    Pawn(){}
}; 

#endif 