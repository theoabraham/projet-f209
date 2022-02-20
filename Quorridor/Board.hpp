#include "WallCell.h"
#include "PawnCell.h"
#include "Wall.h"
#include <string>

#include "iostream"

class Board{
    private:
        int size=9;
        std::vector<std::vector<MotherCell>> matrix;
        const int boardSize;
    public:
        explicit Board(int nsize=9);
        void printBoard();
        void bindCells();
        std::vector<std::vector<MotherCell>> getMatrix(){
        return matrix;
        }
};