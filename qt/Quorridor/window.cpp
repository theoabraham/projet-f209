#include <iostream>
#include <QtWidgets>
#include "window.h"


Window::Window(QWidget *parent): QWidget(parent){
    setWindowTitle("Quoridor");
    mainLayout = new QVBoxLayout(this);

    boardGame();
    wallSelection();
    mainLayout->addLayout(boardGUI);
    mainLayout->addLayout(wallsPlacement);
}

void Window::resetVar(){
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


void Window::boardGame(){
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

void Window::wallSelection(){
    wallsPlacement = new QHBoxLayout();
    QLabel *text = new QLabel("Murs: ");

    murH = new QLabel(this);
    murH->setStyleSheet("QLabel { background-color : black; color : black; }");
    murH->setFixedSize(QSize(100,5));

    murV = new QLabel(this);
    murV->setStyleSheet("QLabel { background-color : black; color : black; }");
    murV->setFixedSize(QSize(5,100));

    wallsPlacement->addWidget(text);
    wallsPlacement->addWidget(murH);
    wallsPlacement->addWidget(murV);
}

