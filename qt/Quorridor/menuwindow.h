#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QtWidgets>
#include "gamewindow.h"
#include "friendlistwidget.h"
#include "rankwidget.h"
#include "lobbywidget.h"

class MenuWindow : public QMainWindow
{
    Q_OBJECT

private:
    //MenuWindow widgets
    QTabWidget *menuSelection;
    QWidget *play;
    QWidget *lobby;
    FriendListWidget *friends;
    RankWidget *ranking;

    //NewGame widgets
    QVBoxLayout *playLayout;
    QLabel *playIntro;
    QGridLayout *options;
    QLabel *modeTitle;
    QComboBox *modeChoice;
    QLabel *playersTitle;
    QComboBox *playersChoice;
    QPushButton *startButton;
    GameWindow *game;

    //Join widgets
    QVBoxLayout *joinLayout;
    QLabel *lobbyIntro;
    LobbyWidget *rowLobby;

public:
    MenuWindow(QMainWindow *parent=0);

    ~MenuWindow();

    void setStart();

    void setJoin();

public slots:
    void startGame();
};

#endif // MENUWINDOW_H
