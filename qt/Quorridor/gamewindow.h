#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include "friendlistwidget.h"
#include "rankwidget.h"
#include "chatroom.h"
#include "wallsBox.h"
#include "wallCell.h"
#include "boardgui.h"

class GameWindow : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *centralLayout;
    QTabWidget *gameViews;
    QWidget *game;
    FriendListWidget *friends;
    RankWidget *ranking;
    BoardGUI *boardgui;

    QGridLayout *mainLayout;
    Chatroom *chatroom;

public:
    GameWindow(QWidget *parent=0);

    ~GameWindow();

    void setGame();
};


#endif // WINDOW_H
