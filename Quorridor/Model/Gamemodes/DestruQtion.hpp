#include "../Board.hpp"
#include "../Piece.hpp"

class DestruQtionWall: Wall {
        std::vector<Wall *> triplet;
    public:
        explicit DestruQtionWall(Position position, std::string direction): Wall(position, direction) {}
        void setTriplet(Wall *otherWall) {triplet.push_back(otherWall);}
        ~DestruQtionWall() {for (auto w: triplet) delete w;}
};

class DestruQtionBoard: Board {
    public:
        explicit DestruQtionBoard(int nplayer, int size=9, const int START_WALL=99): Board(nplayer, size, START_WALL) {}
        bool checkWall(std::string &direction, Position &next_pos) override;
        bool destroyWall(std::shared_ptr<Piece> wall);
};