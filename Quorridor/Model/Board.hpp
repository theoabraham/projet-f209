#include "MotherCell.hpp"
#include <string>
#include <array>

#include "iostream"

#pragma once 

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