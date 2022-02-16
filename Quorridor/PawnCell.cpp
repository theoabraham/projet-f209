//
// Created by Mark Dimitrov on 15/02/2022.
//

#include "PawnCell.h"

bool PawnCell::occupied() {
    return cellItem;
}

void PawnCell::set(Item *item) {
    cellItem = item;
}

Item *PawnCell::getItem() {
    return MotherCell::getItem();
}
