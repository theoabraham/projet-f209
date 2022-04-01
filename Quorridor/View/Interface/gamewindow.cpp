#include <iostream>
#include <QtWidgets>
#include "gamewindow.h"


GameWindow::GameWindow(QWidget *parent): QWidget(parent){
   setMinimumSize(QSize(500,400));

   mainLayout = new QGridLayout(this);
   boardgui = new BoardGUI();
   mainLayout->addWidget(boardgui,0,0,2,1);

   chatroom = new Chatroom();
   mainLayout->addWidget(chatroom,0,1);

   leaveButton = new QPushButton("Quit and Save");
   connect(leaveButton, SIGNAL(clicked()), this, SLOT(leaveAndSave()));
   mainLayout->addWidget(leaveButton,1,1);
}

void GameWindow::leaveAndSave() {
    //TODO sauvegarder dans le serveur client
    confirmation = new QMessageBox();
    confirmation->setText("Do you really want to quit ?");
    confirmation->setWindowTitle("Are you sure ?");
    confirmation->setIcon(QMessageBox::Question);
    confirmation->setStandardButtons(QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
    int choice = confirmation->exec();
    switch (choice) { //TODO interpréter retour d'exec()
    case QMessageBox::Discard:
        break;
    case QMessageBox::Cancel:
        break;
    case QMessageBox::Save:
        break;
    default:
        break;
    }
}
