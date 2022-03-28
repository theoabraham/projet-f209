#include "lobbywidget.h"

LobbyWidget::LobbyWidget(QWidget *parent) : QWidget(parent)
{
    row = new QHBoxLayout(this);
    lobbyNb = new QLabel("Lobby #1");
    row->addWidget(lobbyNb);
    joinButton = new QPushButton("Join");
    connect(joinButton, SIGNAL(clicked()), this, SLOT(joinGame()));
    row->addWidget(joinButton);
}

LobbyWidget::~LobbyWidget() {
    delete row;
    delete lobbyNb;
    delete joinButton;
    delete game;
}

void LobbyWidget::joinGame() {
    game = new GameWindow();
    game->show();
}
