#ifndef PROJET_F209_QQQUORIDOR_H
#define PROJET_F209_QQQUORIDOR_H

#include "../Board"

class QQQuoridorBoard: Board {
public:
    QQQuoridorBoard(int nplayer, int size=15, int walls=20): Board(nplayer, size, walls) {}
    bool checkInput(std::string &input, int currentP) override;
}

#endif //PROJET_F209_QQQUORIDOR_H
