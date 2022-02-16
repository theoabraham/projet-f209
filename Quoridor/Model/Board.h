#include "WallCell.h"
#include "PawnCell.h"
#include "MotherCell.hpp"
#include <string>
#include <array>

#include "iostream"

#ifndef BOARD_H
#define BOARD_H

class Board{
    private:
        int size=9;
        int boardSize;
        
        std::vector<std::vector<MotherCell> > matrix;
    
    public:
        explicit Board(int size=9);
        void bindCells();
        std::vector<std::vector<MotherCell> > getMatrix() {return matrix;}
        int getBoardSize() const {return boardSize;}

        void newGame(); 
};

#endif