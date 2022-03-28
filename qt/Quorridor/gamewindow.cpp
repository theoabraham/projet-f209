#include <iostream>
#include <QtWidgets>
#include "gamewindow.h"


GameWindow::GameWindow(QWidget *parent): QWidget(parent){
   setWindowTitle("Quoridor");
   setMinimumSize(900,710);

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
   boardgui = new BoardGUI();
   mainLayout->addWidget(boardgui,0,0,2,1);

   chatroom = new Chatroom();
   mainLayout->addWidget(chatroom,1,1);

   leaveButton = new QPushButton("Quit and Save");
   connect(leaveButton, SIGNAL(clicked()), this, SLOT(leaveAndSave()));
   mainLayout->addWidget(leaveButton,0,1);
}

void GameWindow::leaveAndSave() {
    //TODO sauvegarder dans le serveur client
    confirmation = new QMessageBox();
    confirmation->setText("Do you really want to quit ?");
    confirmation->setWindowTitle("Are you sure ?");
    confirmation->addButton(QMessageBox::Discard);
    confirmation->addButton(QMessageBox::Cancel);
    confirmation->addButton(QMessageBox::Save);
    confirmation->show();
    //close();
}
