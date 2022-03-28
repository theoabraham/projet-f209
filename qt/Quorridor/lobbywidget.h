#ifndef LOBBYWIDGET_H
#define LOBBYWIDGET_H

#include <QtWidgets>
#include "gamewindow.h"

class LobbyWidget : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout *row;
    QLabel *lobbyNb;
    QPushButton *joinButton;
    GameWindow *game;
public:
    LobbyWidget(QWidget *parent=0);

    ~LobbyWidget();

public slots:
    void joinGame();
};

#endif // LOBBYWIDGET_H
