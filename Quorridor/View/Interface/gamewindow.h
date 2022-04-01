#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include "friendlistwidget.h"
#include "rankwidget.h"
#include "chatroom.h"
#include "wallsBox.h"
#include "wallCell.h"
#include "boardgui.h"

class ClientGUI;

class GameWindow : public QWidget
{
    Q_OBJECT

private:
    ClientGUI *client;

    QGridLayout *mainLayout;
    Chatroom *chatroom;
    BoardGUI *boardgui;
    QPushButton *leaveButton;

public:
    GameWindow(ClientGUI *client, QWidget *parent=0);

    ~GameWindow();

    QPushButton* getLeaveButton() {return leaveButton;}
};


#endif // WINDOW_H
