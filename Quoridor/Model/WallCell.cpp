//
// Created by Mark Dimitrov on 15/02/2022.
//

#include "WallCell.h"


bool WallCell::occupied() {
    return cellItem;
}


void WallCell::set(Item *item) {
    cellItem = item;
}

Item *WallCell::getItem() {
    return cellItem;
}

