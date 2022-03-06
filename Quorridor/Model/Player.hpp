#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <utility>
#include <vector>
#include "Piece.hpp"

class Player {
    int id;
    std::shared_ptr<Pawn> pawn; 
    int walls; 
public:    
    Player(int id, std::shared_ptr<Pawn> pawn, int walls):id{id}, pawn{std::move(pawn)}, walls{walls} {}
    
    std::shared_ptr<Pawn> getPawn(){return pawn;}
    Position getPawnPos() {return pawn->getPos();}
    void setPawnPos(Position pos) {pawn->setPos(pos);}
    int getWalls() {return walls;}

    int getId() const{return id;};

    void useWall(){walls--;};
    bool hasWalls() const{return walls;};
    void addWall(){walls++;};
};

#endif