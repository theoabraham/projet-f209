#ifndef BOARDGUI_H
#define BOARDGUI_H

#include <QtWidgets>
#include <iostream>
#include "wallsBox.h"
#include "wallCell.h"

class BoardGUI : public QWidget
{
    QGridLayout *boardGUI;
    QVBoxLayout *gameLayout;
    WallsBox *wallsPlacement;

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
