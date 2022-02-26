#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <utility>
#include <vector>
#include "Piece.hpp"

class Player {
    int id;
    std::shared_ptr<Pawn> pawn; 
    int walls = 6;  //idée:  décrémenter chaque fois que le joueur place un mur 
public:    
    Player(int id, std::shared_ptr<Pawn> pawn):id{id}, pawn{std::move(pawn)} {}
    
    std::shared_ptr<Pawn> getPawn(){return pawn;}
    Position getPawnPos() {return pawn->getPos();}
    void setPawnPos(Position pos) {pawn->setPos(pos);}
};

#endif