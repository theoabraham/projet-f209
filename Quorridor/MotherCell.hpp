#include "Pawn.hpp"
#include "Wall.h"
#include <vector>
#include "Item.h"
#pragma once

class MotherCell{
protected:
    Item* cellItem;
    std::vector<MotherCell*> neighbours{nullptr, nullptr, nullptr, nullptr};
public:
        MotherCell* getNeighbour(int neighbourPos);
        void blockNeighbour(int neighbourPos);
        void setNeighbours(std::vector<MotherCell*> &neighbours);
        virtual bool occupied();
        virtual void set(Item *item);
        virtual Item* getItem();
        virtual void delItem();
};