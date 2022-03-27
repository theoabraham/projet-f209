#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include "friendlistwidget.h"
#include "rankwidget.h"
#include "chatroom.h"
#include "wallsBox.h"
#include "wallCell.h"

class GameWindow : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *centralLayout;
    QTabWidget *gameViews;
    QWidget *game;
    FriendListWidget *friends;
    RankWidget *ranking;

    QGridLayout *mainLayout;
    QGridLayout *boardGUI;
    WallsBox *wallsPlacement;
    Chatroom *chatroom;

    QLabel *cell;
    WallCell *wallCellH;
    WallCell *wallCellV;

public:
    GameWindow(QWidget *parent=0);

    ~GameWindow();

    void setGame();

    void resetVar();

    void boardGame();
};


#endif // WINDOW_H
