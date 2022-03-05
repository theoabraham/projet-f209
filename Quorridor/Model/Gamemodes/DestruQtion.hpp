#include "../Board.hpp"
#include "../Piece.hpp"

class DestruQtionWall: public Wall {
        std::vector<std::shared_ptr<Piece>> triplet;
    public:
        explicit DestruQtionWall(Position position, std::string direction): Wall(position, direction) {}
        void setTriplet(std::shared_ptr<DestruQtionWall> otherWall) {triplet.push_back(otherWall);}
        std::vector<std::shared_ptr<Piece>> getTriplet() override {return triplet;}

};

class DestruQtionBoard: public Board {
    public:
        explicit DestruQtionBoard(int nplayer, int size=9, const int START_WALL=99): Board(nplayer, size, START_WALL) {}

        void placeWall(std::string &direction, Position &pos) override;
        bool checkWall(std::string &direction, Position &target_pos) override;
        void destroyWall(std::shared_ptr<Piece> wall);

        ~DestruQtionBoard() {};

}; 