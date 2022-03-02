#include "../Board.hpp"

const int WALL_COUNT = 99;

class DestrucQtionBoard: Board {
    private:

    public:
        /**
         * 
        **/
        DestrucQtionBoard(int size=9): Board(size, WALL_COUNT) {}

};