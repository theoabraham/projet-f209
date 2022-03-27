#include <iostream>
#include <QtWidgets>
#include "gamewindow.h"


GameWindow::GameWindow(QWidget *parent): QWidget(parent){
   setWindowTitle("Quoridor");
   setMinimumSize(790,685);

   centralLayout = new QHBoxLayout(this);
   gameViews = new QTabWidget();
   game = new QWidget();
   setGame();
   gameViews->addTab(game, "Game");
   friends = new FriendListWidget();
   gameViews->addTab(friends, "Friends");
   ranking = new RankWidget();
   gameViews->addTab(ranking, "Ranking");
   centralLayout->addWidget(gameViews);
}
GameWindow::~GameWindow() {
   delete centralLayout;
   delete gameViews;
   delete game;
   delete friends;
   delete ranking;
   delete mainLayout;
   delete boardgui;
   delete chatroom;
}

void GameWindow::setGame() {
   mainLayout = new QGridLayout(game);
   boardgui = new BoardGUI;
   mainLayout->addWidget(boardgui,0,0);

   chatroom = new Chatroom();
   mainLayout->addWidget(chatroom,0,1,2,1);
}
