#include "boardgui.h"

BoardGUI::BoardGUI(QWidget *parent): QWidget(parent){
    setWindowTitle("Quoridor");
    gameLayout = new QVBoxLayout(this);
    boardGame();
    gameLayout->addLayout(boardGUI);

    wallsPlacement = new WallsBox;
    wallsPlacement->setFixedSize(QSize(120,100));
    gameLayout->addWidget(wallsPlacement);
}

BoardGUI::~BoardGUI(){
    delete boardGUI;
    delete gameLayout;
    delete wallsPlacement;

    delete cell;
    delete wallCellH;
    delete wallCellV;
    delete wallCell;
}

void BoardGUI::resetVar(){
    //Cases pions:
    cell = new QLabel(this);
    cell->setStyleSheet("QLabel { background-color : brown; color : brown; }");
    cell->setFixedSize(QSize(50,50));

    //Cases murs horizontales:
    wallCellH = new WallCell(false);
    wallCellH->setFixedSize(QSize(50,10));

    //Cases murs verticales:
    wallCellV = new WallCell(false);
    wallCellV->setFixedSize(QSize(10,50));

    //Cases milieu des murs
    wallCell = new WallCell(true);
    wallCell->setFixedSize(QSize(10,10));
}


void BoardGUI::boardGame(){
    boardGUI = new QGridLayout();
    boardGUI->setVerticalSpacing(0);
    boardGUI->setHorizontalSpacing(0);

    for(int i=0;i<17;i++){
        for(int j=0;j<17;j++){

            resetVar();
            if (j%2==1 && i%2==0) {
                boardGUI->addWidget(wallCellV, i,j);
            }
            else if (i%2==1 && j%2==0){
                boardGUI->addWidget(wallCellH,i,j);
            }
            else if (i%2==1 && j%2==1) {
                boardGUI->addWidget(wallCell, i,j);
            }
            else {
                boardGUI->addWidget(cell,i,j);
            }

            if ((i==0) && (j==8)){
                cell->setPixmap(QPixmap(":/images/pion_blanc.png"));
            }
            if ((i==16) && (j==8)){
                cell->setPixmap(QPixmap(":/images/pion_noir.png"));
            }
        }
    }
}

