//
// Created by Mark Dimitrov on 15/02/2022.
//
#include "Player.h"
#include "Position.h"
#include "Item.h"
#include <vector>
#ifndef QUORRIDOR_WALL_H
#define QUORRIDOR_WALL_H


class Wall : public Item{
private:
    std::vector<Position> positions;
public:
    Wall(std::vector<Position> occupiedCells);
    std::vector<Position> getPos();
};


#endif //QUORRIDOR_WALL_H
