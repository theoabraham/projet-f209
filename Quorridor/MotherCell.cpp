#include "MotherCell.hpp"

MotherCell* MotherCell::getNeighbour(int neighbourPos){
    return neighbours[neighbourPos];
}

void MotherCell::blockNeighbour(int neighbourPos){
    neighbours[neighbourPos] = nullptr;
}

void MotherCell::setNeighbours(std::vector<MotherCell *> &neighboursList) {
    neighbours = neighboursList;
}

bool MotherCell::occupied() {
    return false;
}

void MotherCell::set(Item *item) {
    cellItem = item;
}

Item *MotherCell::getItem() {
    return cellItem;
}

void MotherCell::delItem() {
    cellItem = nullptr;
}



