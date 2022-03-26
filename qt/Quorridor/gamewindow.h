#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include "friendlistwidget.h"
#include "rankwidget.h"
#include "dragwidget.h"

class GameWindow : public QWidget
{
    Q_OBJECT

private:
    QTabWidget *gameViews;
    QWidget *game;
    FriendListWidget *friends;
    RankWidget *ranking;

    QGridLayout *mainLayout;
    QGridLayout *boardGUI;
    QHBoxLayout *wallsPlacement;
    QVBoxLayout *chatroom;

    QLabel *label;
    QLabel *label2;
    QLabel *label3;
    QLabel *murH;
    QLabel *murV;
    QLineEdit *chatEntry;
    QTextEdit *chatDisplay;
    QLabel *chatTitle;

public:
    GameWindow(QWidget *parent=0);

    ~GameWindow();

    void setGame();

    void resetVar();

    void boardGame();

    void wallSelection();

    void setChatroom();

    QString getMessage();

public slots:
    void runChatroom();
};


#endif // WINDOW_H
