#include "DestruQtion.hpp"

bool DestruQtionBoard::checkWall(std::string &direction, Position &target_pos){
    int posX, posY;
    if (direction == "H") {
        if (target_pos.getY() > 0 && (target_pos.getX() + 2 < boardSize)){
            for (int i = 0; i < 3; i++) {
                posY = target_pos.getY() - 1; // décalage vers les WallCell
                posX = target_pos.getX() + i; // longueur du mur
                if (matrix[posY][posX]->occupied()) return destroyWall(matrix[posY][posX]->getPiece());
            }
        } 
        else return false;    
    }
    else {
        if (target_pos.getY() > 0 && (target_pos.getX() + 2 <= boardSize)){
            for (int i = 0; i < 3; i++) {
            posY = target_pos.getY() - i; // largeur du mur
            posX = target_pos.getX() + 1; // décalage vers les WallCell
            if (matrix[posY][posX]->occupied()) return destroyWall(matrix[posY][posX]->getPiece());
            }
        }
        else return  false; 
    }
    return true;
}