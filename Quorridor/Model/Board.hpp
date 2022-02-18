#ifndef BOARD_HPP
#define BOARD_HPP

#include "MotherCell.hpp"
#include "Player.hpp"
#include <string>
#include <array>
#include <memory>

#include "iostream"


class Board{
    private:
        int size=9;
        int boardSize;
        
        std::vector<std::vector<MotherCell> > matrix;

        std::vector<std::vector<Player> > pawns; 
    
    public:
        explicit Board(int size=9);
        void bindCells();
        std::vector<std::vector<MotherCell> > getMatrix() {return matrix;}
        int getBoardSize() const {return boardSize;}

        void newGame(int nPlayer=2); 
};

#endif