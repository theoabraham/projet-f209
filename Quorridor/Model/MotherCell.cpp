#include "MotherCell.hpp"

#include <utility>


std::shared_ptr<MotherCell> MotherCell::getNeighbour(Position &neighbourPos){
    switch (neighbourPos.getX()) {
        case (0):
            switch (neighbourPos.getY()) {
                case (1):
                    return neighbours[0];
                case (-1):
                    return neighbours[2];
            }
        case (1):
            if(neighbourPos.getY() == 0){
                return neighbours[1];
            }
        case (-1):
            if (neighbourPos.getY() == 0){
                return neighbours[3];
            }
    }
    return nullptr;
}


bool MotherCell::occupied() {
    if (cellPiece ) return true;
    else return false;
}


