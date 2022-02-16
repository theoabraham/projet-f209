//
// Created by Mark Dimitrov on 15/02/2022.
//
#include "MotherCell.hpp"
#ifndef QUORRIDOR_PAWNCELL_H
#define QUORRIDOR_PAWNCELL_H


class PawnCell : public MotherCell{
public:
    bool occupied() override;
    Item* getItem() override;
    void set(Item *item) override;
};


#endif //QUORRIDOR_PAWNCELL_H
