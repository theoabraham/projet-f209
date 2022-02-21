#include "MotherCell.hpp"

#include <utility>



//MotherCell:
std::shared_ptr<MotherCell> MotherCell::getNeighbour(int neighbourPos){
    return neighbours[neighbourPos];
}

void MotherCell::blockNeighbour(int neighbourPos){
    neighbours[neighbourPos] = nullptr;
}

bool MotherCell::occupied() {
    if (cellPiece) return true;
    else return false;
}

void MotherCell::set(std::shared_ptr<Piece> piece) {
    cellPiece = piece;
}

std::shared_ptr<Piece> MotherCell::getPiece() {
    return cellPiece;
}

void MotherCell::delPiece() {
    cellPiece = nullptr;
}

bool MotherCell::isNeighbour(Position neighbourPos) {
    switch (neighbourPos.getX()) {
        case (0):
            switch (neighbourPos.getY()) {
                case (1):
                    return (neighbours[0] != nullptr);
                case (-1):
                    return (neighbours[2] != nullptr);
            }
        case (1):
            if(neighbourPos.getY() == 0){
                return (neighbours[1] != nullptr);
            }
        case (-1):
            if (neighbourPos.getY() == 0){
                return (neighbours[3] != nullptr);
            }
    }
    return false;
}

void MotherCell::setNeighbours(std::vector<std::shared_ptr<MotherCell>> &neighbourVector) {
    neighbours = neighbourVector;
}


//PawnCell:

//Fonction occupied mieux dans mothercell

/*
bool PawnCell::occupied() {
    if (cellPiece != 0) return true; 
    else return false;
}
*/

void PawnCell::set(std::shared_ptr<Piece> piece) {
    cellPiece = piece;
}

std::shared_ptr<Piece> PawnCell::getPiece() {
    return MotherCell::getPiece();
}


//WallCell: 

/*
bool WallCell::occupied() {
    if (cellPiece) return true; 
    else return false; 
}
*/

void WallCell::set(std::shared_ptr<Piece> piece) {
    cellPiece = piece;
}

std::shared_ptr<Piece> WallCell::getPiece() {
    return cellPiece;
}

