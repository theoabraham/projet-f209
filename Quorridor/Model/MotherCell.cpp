#include "MotherCell.hpp"

#include <utility>



//MotherCell:
bool MotherCell::isNeighbour(Position neighbourPos) {

    switch (neighbourPos.getX()) {
        case (0):
            switch (neighbourPos.getY()) {
                case (2):
                    return (neighbours[0] != nullptr);
                case (-2):
                    return (neighbours[2] != nullptr);
            }
        case (2):
            if(neighbourPos.getY() == 0){
                return (neighbours[1] != nullptr);
            }
        case (-2):
            if (neighbourPos.getY() == 0){
                return (neighbours[3] != nullptr);
            }
    }
    return false;
}

bool MotherCell::occupied() {
    if (cellPiece) return true;
    else return false;
}


//PawnCell:
void PawnCell::setPiece(std::shared_ptr<Piece> piece) {
    cellPiece = piece;
}

std::shared_ptr<Piece> PawnCell::getPiece() {
    return MotherCell::getPiece();
}


//WallCell: 
void WallCell::setPiece(std::shared_ptr<Piece> piece) {
    cellPiece = piece;
}

std::shared_ptr<Piece> WallCell::getPiece() {
    return cellPiece;
}

