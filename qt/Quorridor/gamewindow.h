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

    QGridLayout *mainLayout;
    Chatroom *chatroom;
    BoardGUI *boardgui;
    QPushButton *leaveButton;
    QMessageBox *confirmation;

public:
    GameWindow(QWidget *parent=0);

    ~GameWindow();

    void setGame();

public slots:
    void leaveAndSave();
};


#endif // WINDOW_H
