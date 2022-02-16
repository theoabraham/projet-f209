//
// Created by Mark Dimitrov on 15/02/2022.
//
#include "MotherCell.hpp"
#ifndef QUORRIDOR_WALLCELL_H
#define QUORRIDOR_WALLCELL_H


class WallCell: public MotherCell{
public:
    bool occupied() override;
    Item* getItem() override;
    void set(Item *item) override;
};


#endif //QUORRIDOR_WALLCELL_H
