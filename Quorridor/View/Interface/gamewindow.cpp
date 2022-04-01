#include <iostream>
#include <QtWidgets>
#include "gamewindow.h"


GameWindow::GameWindow(ClientGUI *client, QWidget *parent): QWidget(parent), client{client} {
   setMinimumSize(QSize(500,400));

   mainLayout = new QGridLayout(this);
   boardgui = new BoardGUI(client);
   mainLayout->addWidget(boardgui,0,0,2,1);

   chatroom = new Chatroom();
   mainLayout->addWidget(chatroom,0,1);

   leaveButton = new QPushButton("Quit and Save");
   mainLayout->addWidget(leaveButton,1,1);
}

GameWindow::~GameWindow() {
    delete mainLayout;
    delete chatroom;
    delete boardgui;
    delete leaveButton;
}

