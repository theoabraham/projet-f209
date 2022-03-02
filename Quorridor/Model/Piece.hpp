#ifndef PIECE_HPP
#define PIECE_HPP

#include "Position.hpp"
//#include "Player.hpp"
#include <memory>
#include <vector>
#include <iostream>
#include <string>

class Piece {
public:
    virtual Position getPos()=0; 
    virtual void setPos(Position pos)=0; 
    virtual ~Piece(){} 
};


class Wall : public Piece{
private:
    Position position; 
    std::string direction;
public:
    Wall(Position position, std::string direction): position(position), direction(direction) {}; 
    Position getPos() override {return position;}
    void setPos(Position pos) override {position = pos;}
    
    bool isHwall() {return direction=="H";}
}; 

class Pawn : public Piece{
    Position position;
public: 
    Pawn(Position position): position{position}{}
    Position getPos() override {return position;}
    void setPos(Position pos) override {position = pos;}
}; 

#endif 