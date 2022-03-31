#ifndef BOARDGUI_H
#define BOARDGUI_H

#include <QtWidgets>
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include "wallsBox.h"
#include "wallCell.h"
#include "pawncell.h"
#include "friend.h"

class BoardGUI : public QWidget
{
    Q_OBJECT

public:
    BoardGUI(QWidget *parent=0);

    ~BoardGUI();

    void resetVar();

    void boardGame();

    void bindWalls();

private:

    QGridLayout *boardGUI;
    QGridLayout *gameLayout;
    QHBoxLayout *wallLayout;
    WallsBox *wallsPlacement;
    QHBoxLayout *opponentSpace;
    Friend *opponent;

    QLabel *cellLabel;
    PawnCell *cell;

    WallCell *wallCellH;
    WallCell *wallCellV;
    WallCell *wallCell;

    std::vector<std::vector< WallCell *> > boardGUIMatrix;
};


#endif // BOARDGUI_H
