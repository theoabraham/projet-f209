#include "../../Controller/Game.hpp"
#include "../Board.hpp"

#include <stack>
#include <random>

class MinosBoard: public Board {
    public:
        explicit MinosBoard(int nplayer, int size=9, int START_WALL=4): Board(nplayer, size, START_WALL) {}

        void placeWall(std::string &direction, Position &pos) override {Board::placeWall(direction, pos);}
        bool checkWall(std::string &direction, Position &pos) override {return Board::checkWall(direction, pos);}
        bool checkInput(std::string &input, int currentP) override {return Board::checkInput(input, currentP);}
        void destroyWall(const std::string& direction, Position& pos) override {Board::destroyWall(direction, pos);}
};



class MinosGame: public Game {
    private:
        int wallsToPlace = 10;
        const int wallsToDestroy = wallsToPlace;
        int count = 0;
        std::stack<Position> placedWalls;
        std::stack<std::string> placedWallsDirections;
    public:
        explicit MinosGame(std::shared_ptr<Board> model, std::shared_ptr<DisplayBoard> view): Game(model, view) {}

        void createLabyrinth();
        void destroyLabyrinth();

        void start() override;
};