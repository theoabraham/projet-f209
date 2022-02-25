#ifndef PIECE_HPP
#define PIECE_HPP

#include "Position.hpp"
//#include "Player.hpp"
#include <memory>
#include <vector>
#include <iostream>

class Piece {
    virtual Position getPos()=0; 
    virtual void setPos(Position pos)=0; 
};


class Wall : public Piece{
private:
    Position position; //Position et non vecteur de position --> sa position sera les cases jms utilisées dans la matrice (celles qui ont une valeur paire et une impaire)
public:
    Position getPos() override;
    void setPos(Position pos) override; 
};

class Pawn : public Piece{
    Position position;
public: 
    Pawn(Position initialPos);
    Position getPos() override {return position;}
    void setPos(Position pos) override {position = pos;}
}; 

#endif 