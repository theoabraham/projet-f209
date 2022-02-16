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
    return false;
}

void MotherCell::set(Piece *Piece) {
    cellPiece = Piece;
}

Piece *MotherCell::getPiece() {
    return cellPiece;
}

void MotherCell::delPiece() {
    cellPiece = nullptr;
}


//PawnCell:
bool PawnCell::occupied() {
    return cellPiece;
}

void PawnCell::set(Piece *Piece) {
    cellPiece = Piece;
}

Piece *PawnCell::getPiece() {
    return MotherCell::getPiece();
}


//WallCell: 
bool WallCell::occupied() {
    return cellPiece;
}


void WallCell::set(Piece *Piece) {
    cellPiece = Piece;
}

Piece *WallCell::getPiece() {
    return cellPiece;
}

