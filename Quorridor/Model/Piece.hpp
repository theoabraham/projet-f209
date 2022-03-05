#ifndef PIECE_HPP
#define PIECE_HPP

#include "Position.hpp"
#include <memory>
#include <utility>
#include <vector>
#include <iostream>
#include <string>

struct Piece {

    virtual std::vector<std::shared_ptr<Piece>> getTriplet()=0;

    virtual Position getPos()=0;  
    virtual void setPos(Position pos)=0; 
    virtual bool isHWall()=0; 
    virtual int getID() =0; 
    virtual ~Piece(){} 
};


class Wall : public Piece{
private:
    Position position; 
    std::string direction;
    virtual std::vector<std::shared_ptr<Piece>> getTriplet() override {}; // Fausse virtuelle pour permettre la configuration OOP de la classe DestruQtionWall
public:
    Wall(Position position, std::string direction): position(position), direction(std::move(direction)) {};
    Position getPos() override {return position;}
    void setPos(Position pos) override {position = pos;}
    
    int getID() override {return 7;}
    bool isHWall() override {return direction=="H";}

}; 

class Pawn : public Piece{
    Position position;
    int id; //Joueur auquel appartient le pion
    virtual std::vector<std::shared_ptr<Piece>> getTriplet() override {}; // Fausse virtuelle pour permettre la configuration OOP de la classe DestruQtionWall
public: 
    Pawn(Position position, int id): position{position}, id{id} {}
    Position getPos() override {return position;}
    void setPos(Position pos) override {position = pos;}
    
    int getID() override {return id;}
    bool isHWall() override {return false;}


}; 

#endif 