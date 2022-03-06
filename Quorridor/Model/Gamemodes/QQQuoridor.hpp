#ifndef QQQUORIDOR_HPP
#define QQQUORIDOR_HPP

#include "../Board.hpp"
#include <vector>

class QQQuoridorBoard: public Board {
public:
    explicit QQQuoridorBoard(int nplayer, int size=15, const int START_WALL=20): Board(nplayer, size, START_WALL) {}

    /**
    * @brief sépare l'input en deux coups
    * @param input : coup entré par le joueur
    * @return vector<string> : chaque élément du vecteur contient un coup
    */
    std::vector<std::string> divideInput(std::string &input);
    bool checkInput(std::string &input, int currentP) override;

    void placeWall(std::string &direction, Position &pos) override {Board::placeWall(direction, pos);}
    bool checkWall(std::string &direction, Position &pos) override {return Board::checkWall(direction, pos);}
    void destroyWall(const std::string& direction, Position& pos) override {Board::destroyWall(direction, pos);}
};

class QQQuoridorPosition: public Position {
public:
    QQQuoridorPosition(std::string pos);
    Position operator=(const Position& other) override;

    
};

#endif
