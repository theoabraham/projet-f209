#include <iostream>
#include <vector>
#include "Pawn.hpp"

class Cell {
    std::vector<Cell*> _neighbours;
    Pawn* _occupied;
    char _hasWall;

public:
    Cell(): _occupied{nullptr}, _hasWall{'N'} {}

    	void setNeighbours(std::vector <Cell*> newNeighbours) {
    	    this->_neighbours = newNeighbours;
    	}
        
        Cell* getNeighbour(int neighbourLoc) {
            return _neighbours[neighbourLoc];
        }

        void blockNeighbour(int neighbourLoc) {
            _neighbours[neighbourLoc] = nullptr;
        }

        void removePawn() {
            _occupied = nullptr;
        }

    	void acceptPawn(Pawn* newPawn, Cell* oldCell) {
    	    this->_occupied = newPawn;
    	    oldCell->removePawn();
    	}

        void receiveWall(char wallType) {
            if (wallType == 'H') {
                _neighbours[0]->blockNeighbour(2);
                blockNeighbour(0);
            }
            if (_neighbours[1] != nullptr) {
                _neighbours[1]->getNeighbour(0)->blockNeighbour(2);
                _neighbours[1]->blockNeighbour(0);
            }

            if (wallType == 'V') {
                _neighbours[1]->blockNeighbour(3);
                blockNeighbour(1);
            }

            if (_neighbours[0]) {
                _neighbours[0]->getNeighbour(1)->blockNeighbour(3);
                _neighbours[0]->blockNeighbour(1);
            }
        }
};