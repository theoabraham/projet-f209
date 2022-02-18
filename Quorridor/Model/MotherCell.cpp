#include "MotherCell.hpp"



//MotherCell:
MotherCell* MotherCell::getNeighbour(int neighbourPos){
    return neighbours[neighbourPos];
}

void MotherCell::blockNeighbour(int neighbourPos){
    neighbours[neighbourPos] = nullptr;
}

void MotherCell::setNeighbours(std::vector<MotherCell *> &neighboursList) {
    neighbours = neighboursList;
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

