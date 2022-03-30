#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QtWidgets>
#include "gamewindow.h"
#include "friendlistwidget.h"
#include "rankwidget.h"
#include "login.h"

class MenuWindow : public QMainWindow
{
    Q_OBJECT

private:
    //MenuWindow widgets
    QTabWidget *menuSelection;
    Login *login;
    SignUp *signUp;
    QWidget *play;
    QWidget *currentPlay;
    QWidget *lobby;
    FriendListWidget *friends;
    RankWidget *ranking;

    //Play widgets
    QVBoxLayout *playLayout;
    QLabel *playIntro;
    QGridLayout *options;
    QLabel *modeTitle;
    QComboBox *modeChoice;
    QLabel *playersTitle;
    QComboBox *playersChoice;
    QPushButton *startButton;

    //NewGame widgets
    QHBoxLayout *newGameLayout;
    GameWindow *game;

    //Join widgets
    QVBoxLayout *joinLayout;
    QLabel *lobbyIntro;
    QHBoxLayout *row;
    QLabel *lobbyNb;
    QPushButton *joinButton;

public:
    MenuWindow(QMainWindow *parent=0);

    void setStart();

    void setJoin();

public slots:
    void startGame();

    void joinGame();

    void launchMenu();

    void createAccount();
};

#endif // MENUWINDOW_H
