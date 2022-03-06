#ifndef PIECE_HPP
#define PIECE_HPP

#include "Position.hpp"
#include <memory>
#include <utility>
#include <vector>
#include <iostream>
#include <string>

class Piece {
public:
    virtual Position getPos()=0;  
    virtual void setPos(Position pos)=0; 
    virtual int getID() =0; 
    
    virtual std::string wallD()=0;
    virtual bool isWall() =0; 
    virtual ~Piece(){} 
};


class Wall : public Piece{
private:
    Position position; 
    std::string direction;
public:
    Wall(Position position, std::string direction): position(position), direction(std::move(direction)) {};
    Position getPos() override {return position;}
    void setPos(Position pos) override {position = pos;}
    
    int getID() override {return 7;}
    
    std::string wallD(){return direction;}
    bool isWall() override {return true;} 
}; 

class Pawn : public Piece{
    Position position;
    int id; //Joueur auquel appartient le pion 
public: 
    Pawn(Position position, int id): position{position}, id{id} {}
    Position getPos() override {return position;}
    void setPos(Position pos) override {position = pos;}
    
    int getID() override {return id;}
    std::string wallD() override {return nullptr;}

    bool isWall() override {return false;} 
}; 

#endif 