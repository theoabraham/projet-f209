#include "../Board.hpp"
#include "../Piece.hpp"

class DestruQtionWall: Wall {
        Wall *twin;
    public:
        explicit DestruQtionWall(Position position, std::string direction): Wall(position, direction), twin{nullptr} {}
        void setTwin(Wall* otherWall) {twin = otherWall;}
        ~DestruQtionWall() {delete twin;}
};

class DestruQtionBoard: Board {
    public:
       explicit DestruQtionBoard(int nplayer, int size=9, const int START_WALL=99): Board(nplayer, size, START_WALL) {}

};