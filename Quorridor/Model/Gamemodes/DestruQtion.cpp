#include "DestruQtion.hpp"

bool Board::checkWall(std::string &direction, Position &next_pos){
    int posX, posY;

    
    if (direction == "H") {
        Position wallPos{next_pos.getX(), next_pos.getY() - 1}; // Case cible (voir srd)
        if (wallPos.getY() > 0 && (wallPos.getX() + 2 < boardSize)){
            for (int i = 0; i < 3; i++) {
                posY = next_pos.getY() - 1;
                posX = next_pos.getX() + i;
                if (matrix[posY][posX]->occupied()) return false;
            }
        } 
        else return false;
    }
    else { 
        Position wallPos{next_pos.getX() + 1, next_pos.getY()}; // Case cible (voir srd)
        if (wallPos.getX() < boardSize && (wallPos.getY() - 2 > 0)){
            for (int i = 0; i < 3; i++) {
            posY = next_pos.getY() - i;
            posX = next_pos.getX() + 1;
            if (matrix[posY][posX]->occupied()) return false; 
            }
        }
        else return  false; 
    }
    return true;
}   