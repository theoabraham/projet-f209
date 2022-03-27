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
    QWidget *play;
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
    GameWindow *game;

public:
    MenuWindow(QMainWindow *parent=0);

    ~MenuWindow();

    void setStart();

public slots:
    void startGame();
};

#endif // MENUWINDOW_H
