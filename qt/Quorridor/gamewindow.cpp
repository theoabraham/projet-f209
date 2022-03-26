#include <iostream>
#include <QtWidgets>
#include "gamewindow.h"


GameWindow::GameWindow(QWidget *parent): QWidget(parent){
    setWindowTitle("Quoridor");
    setMinimumSize(778,685);

    gameViews = new QTabWidget(this);
    game = new QWidget();
    setGame();
    gameViews->addTab(game, "Game");
    friends = new FriendListWidget();
    gameViews->addTab(friends, "Friends");
    ranking = new RankWidget();
    gameViews->addTab(ranking, "Ranking");
}
GameWindow::~GameWindow() {
    delete mainLayout;
    delete boardGUI;
    delete wallsPlacement;
    delete chatroom;
    delete label;
    delete label2;
    delete label3;
    delete murH;
    delete murV;
    delete chatEntry;
    delete chatDisplay;
    delete chatTitle;
}

void GameWindow::setGame() {
    mainLayout = new QGridLayout(game);
    boardGame();
    mainLayout->addLayout(boardGUI,0,0);
    wallSelection();
    mainLayout->addLayout(wallsPlacement,1,0);
    setChatroom();
    mainLayout->addLayout(chatroom,0,1,2,1);
}


void GameWindow::resetVar(){
    //Cases pions:
    label = new QLabel(this);
    label->setStyleSheet("QLabel { background-color : brown; color : brown; }");
    label->setFixedSize(QSize(50,50));

    //Cases murs horizontales:
    label2 = new QLabel(this);
    label2->setStyleSheet("QLabel { background-color : white; color : white; }");
    label2->setMaximumSize(QSize(50,10));

    //Cases murs verticales:
    label3 = new QLabel(this);
    label3->setStyleSheet("QLabel { background-color : white; color : white; }");
    label3->setMaximumSize(QSize(10,50));
}


void GameWindow::boardGame(){
    boardGUI = new QGridLayout();
    boardGUI->setVerticalSpacing(0);
    boardGUI->setHorizontalSpacing(0);

    for(int i=0;i<17;i++){
        for(int j=0;j<17;j++){

            resetVar();
            if (i%2==1) boardGUI->addWidget(label2,i,j);
            else if (j%2==1) boardGUI->addWidget(label3, i,j);
            else boardGUI->addWidget(label,i,j);

            if ((i==0) && (j==8)){
                label->setPixmap(QPixmap(":/images/pion_blanc.png"));
            }
            if ((i==16) && (j==8)){
                label->setPixmap(QPixmap(":/images/pion_noir.png"));
            }
        }
    }

}


void GameWindow::wallSelection(){
    wallsPlacement = new QHBoxLayout();
    QLabel *text = new QLabel("Murs: ");

    wallsPlacement->addWidget(text);
    wallsPlacement->addWidget(new DragWidget);
}

void GameWindow::setChatroom(){
    chatroom = new QVBoxLayout();
    chatEntry = new QLineEdit();
    chatEntry->setFixedSize(QSize(250,50));
    chatEntry->setStyleSheet("border: 1px solid black;");
    connect(chatEntry,SIGNAL(returnPressed()), this, SLOT(runChatroom()));
    chatDisplay = new QTextEdit();
    chatDisplay->setReadOnly(true);
    chatDisplay->setFixedSize(QSize(250,530));
    chatDisplay->setStyleSheet("border: 1px solid black; background-color : white;");
    chatTitle = new QLabel("Chatroom");
    chatTitle->setIndent(80);
    QFont font("Arial", 14, QFont::Bold);
    chatTitle->setFont(font);
    chatroom->addWidget(chatTitle);
    chatroom->addWidget(chatDisplay);
    chatroom->addWidget(chatEntry);
}

void GameWindow::runChatroom(){
    QString message = getMessage();
    chatDisplay->append(message);
}

QString GameWindow::getMessage(){
    QString message = chatEntry->text();
    chatEntry->clear();
    return message;
}

