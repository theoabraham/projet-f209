#include "Position.h"
#include "Player.h"
#include "Item.h"
#pragma once
class Pawn : public Item
{
private:
    int id;
    Position position;
    Player* owner;
public:
    Pawn(int id, Position position, Player* player);
    void setPos(Position newPos);
    Position getPos();
    Player getPlayer();
};



