#include "boardgui.h"

BoardGUI::BoardGUI(QWidget *parent): QWidget(parent){   
    gameLayout = new QGridLayout(this);

    wallsPlacement = new WallsBox;
    wallsPlacement->setFixedSize(QSize(120,100));

    boardGame();

    gameLayout->addLayout(boardGUI,0,0,1,2);
    gameLayout->addWidget(wallsPlacement,1,0);

    opponentSpace = new QHBoxLayout();
    opponentSpace->addStretch();
    opponent = new Friend(false);
    opponentSpace->addWidget(opponent);
    gameLayout->addLayout(opponentSpace,1,1);
}

BoardGUI::~BoardGUI(){
    delete boardGUI;
    delete gameLayout;
    delete wallsPlacement;

    delete opponentSpace;
    delete opponent;

    delete cell;
    delete wallCellH;
    delete wallCellV;
    delete wallCell;

    for(int i=0;i<17;i++){
        for(int j=0;j<17;j++){
            delete boardGUIMatrix[i][j];
        }
    }
}

void BoardGUI::resetVar(){
    //Cases pions:
    cell = new PawnCell(wallsPlacement);
    cell->setFixedSize(QSize(50,50));

    //Cases murs horizontales:
    wallCellH = new WallCell(false,wallsPlacement);
    wallCellH->setFixedSize(QSize(50,10));

    //Cases murs verticales:
    wallCellV = new WallCell(false,wallsPlacement);
    wallCellV->setFixedSize(QSize(10,50));

    //Cases milieu des murs
    wallCell = new WallCell(true, wallsPlacement);
    wallCell->setFixedSize(QSize(10,10));

}

void BoardGUI::boardGame(){
    boardGUI = new QGridLayout(this);
    boardGUI->setVerticalSpacing(0);
    boardGUI->setHorizontalSpacing(0);

    for(int i=0;i<17;i++){
        std::vector<WallCell *> line;
        for(int j=0;j<17;j++){
            Pos pos{i,j}; 
            
            resetVar();
            if (j%2==1 && i%2==0) {
                boardGUI->addWidget(wallCellV, i,j);
                line.push_back(wallCellV);
                wallCellV->setPos(pos); 
            }
            else if (i%2==1 && j%2==0){
                boardGUI->addWidget(wallCellH,i,j);
                line.push_back(wallCellH);
                wallCellH->setPos(pos); 
            }
            else if (i%2==1 && j%2==1) {
                boardGUI->addWidget(wallCell, i,j);
                line.push_back(wallCell);
                wallCell->setPos(pos); 
            }
            else {
                boardGUI->addWidget(cell,i,j);
                line.push_back(nullptr);
                cell->setPos(pos); 
            }
            if ((i==0) && (j==8)){
                QPixmap path(":/images/pion_blanc.png");
                cell->setImage(path);
            }
            if ((i==16) && (j==8)){
                QPixmap path(":/images/pion_noir.png");
                cell->setImage(path);
            }
        }
        boardGUIMatrix.push_back(line);
    }
    bindWalls();
}

void BoardGUI::bindWalls(){
    std::vector< WallCell *> vectMurH {nullptr, nullptr};
    std::vector< WallCell *> vectMurV {nullptr, nullptr};
    QString coucou;
    for(int i=0;i<17;i++){
        for(int j=0;j<17;j++){

            if (i%2!=0 && j%2!=0){
                vectMurV[0] = boardGUIMatrix[i-1][j];
                vectMurV[1] = boardGUIMatrix[i+1][j];

                vectMurH[0] = boardGUIMatrix[i][j-1];
                vectMurH[1] = boardGUIMatrix[i][j+1];

                boardGUIMatrix[i][j]->setVectMurH(vectMurH);
                boardGUIMatrix[i][j]->setVectMurV(vectMurV);
            }
        }
    }
}
