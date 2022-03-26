#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QtWidgets>
#include "gamewindow.h"
#include "friendlistwidget.h"
#include "rankwidget.h"

class MenuWindow : public QMainWindow
{
    Q_OBJECT

private:
    //MenuWindow widgets
    QTabWidget *menuSelection;
    QWidget *login;
    QWidget *play;
    FriendListWidget *friends;
    RankWidget *ranking;

    //Login widgets
    QVBoxLayout *loginLayout;
    QLabel *loginIntro;
    QFormLayout *loginEntry;
    QLineEdit *pseudoLine;
    QLineEdit *passwordLine;
    QPushButton *connection;

    //Play widgets
    QVBoxLayout *playLayout;
    QLabel *playIntro;
    QGridLayout *options;
    QLabel *modeTitle;
    QComboBox *modeChoice;
    QLabel *playersTitle;
    QComboBox *playersChoice;
    QPushButton *startButton;
    GameWindow *game;

public:
    MenuWindow(QMainWindow *parent=0);

    void setLogin();

    void setStart();

public slots:
    void startGame();
};

#endif // MENUWINDOW_H
