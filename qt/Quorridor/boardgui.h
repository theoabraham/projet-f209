#ifndef BOARDGUI_H
#define BOARDGUI_H

#include <QtWidgets>
#include <iostream>
#include "wallsBox.h"
#include "wallCell.h"
#include "friend.h"

class BoardGUI : public QWidget
{
    QGridLayout *boardGUI;
    QGridLayout *gameLayout;
    WallsBox *wallsPlacement;
    QHBoxLayout *opponentSpace;
    Friend *opponent;

    QLabel *cell;
    WallCell *wallCellH;
    WallCell *wallCellV;
    WallCell *wallCell;

public:
    BoardGUI(QWidget *parent=0);

    ~BoardGUI();

    void resetVar();

    void boardGame();

};

#endif // BOARDGUI_H
