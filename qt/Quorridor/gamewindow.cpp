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
    delete boardGUI;
    delete wallsPlacement;
    delete chatroom;
    delete cell;
    delete wallCellH;
    delete wallCellV;
}

void GameWindow::setGame() {
    mainLayout = new QGridLayout(game);
    boardGame();
    mainLayout->addLayout(boardGUI,0,0);

    wallsPlacement = new WallsBox;
    wallsPlacement->setFixedSize(QSize(120,100));
    mainLayout->addWidget(wallsPlacement,1,0);

    chatroom = new Chatroom();
    mainLayout->addWidget(chatroom,0,1,2,1);
}


void GameWindow::resetVar(){
    //Cases pions:
    cell = new QLabel(this);
    cell->setStyleSheet("QLabel { background-color : brown; color : brown; }");
    cell->setFixedSize(QSize(50,50));

    //Cases murs horizontales:
    wallCellH = new WallCell;
    wallCellH->setFixedSize(QSize(50,10));

    //Cases murs verticales:
    wallCellV = new WallCell;
    wallCellV->setFixedSize(QSize(10,50));
}


void GameWindow::boardGame(){
    boardGUI = new QGridLayout();
    boardGUI->setVerticalSpacing(0);
    boardGUI->setHorizontalSpacing(0);

    for(int i=0;i<17;i++){
        for(int j=0;j<17;j++){

            resetVar();
            if (j%2==1) boardGUI->addWidget(wallCellV, i,j);
            else if (i%2==1) boardGUI->addWidget(wallCellH,i,j);
            else boardGUI->addWidget(cell,i,j);

            if ((i==0) && (j==8)){
                cell->setPixmap(QPixmap(":/images/pion_blanc.png"));
            }
            if ((i==16) && (j==8)){
                cell->setPixmap(QPixmap(":/images/pion_noir.png"));
            }
        }
    }

}


