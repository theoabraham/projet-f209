#include "Board.hpp"

Board::Board(int size): size{size} {
    newGame(); 
}

void Board::bindCells(){}

void Board:: newGame(){
    boardSize = size*2-1; 
    for (int i = 0; i < size*2-1; i++ ) {
        std::vector<MotherCell> line;
        
        for (int j = 0; j<size*2-1; j++){
            if (( i%2 != 0 and i < boardSize ) or ( j%2 != 0 and j < boardSize)){ //si case impaire --> Murs 
                line.push_back(WallCell());
            } else{ //Cases
                line.push_back(PawnCell());
            } 
        }
        matrix.push_back(line);
    }
    bindCells();
}

