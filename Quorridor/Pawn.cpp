#include "Pawn.hpp"

Pawn::Pawn(int id, Position position, Player* player):
        id{id}, owner{player}, position{position}{};

void Pawn::setPos(Position newPos){
    position = newPos;
}

Position Pawn::getPos(){
    return position;
}

Player Pawn::getPlayer(){
    return *owner;
}

