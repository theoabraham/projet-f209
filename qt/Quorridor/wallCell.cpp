#include <QtWidgets>
#include <iostream>
#include "wallCell.h"


WallCell::WallCell(bool acceptDrop, WallsBox *wall, QWidget *parent)
    : QWidget (parent),wall(wall), acceptDrop(acceptDrop)
{
    setAcceptDrops(acceptDrop);
}

void WallCell::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() != this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
    }
    else {
        event->ignore();
    }
}

void WallCell::dropEvent(QDropEvent *event)
{
    if ((event->mimeData()->hasFormat("application/x-dnditemdata")) && (not receivedItem)) {
        if (event->source() == wall){
            //Si l'item qui est drag viens de WallsBox

            event->acceptProposedAction();

            std::cout<<"dropEvent"<<std::endl;
            if (wall->getTypeOfWall() == "H"){
                setWallColor();
                vectMurH[0]->setWallColor();
                vectMurH[1]->setWallColor();
            }
            else if (wall->getTypeOfWall() == "V"){
                setWallColor();
                vectMurV[0]->setWallColor();
                vectMurV[1]->setWallColor();
            }
            receivedItem = true;
        }

    } else {
        event->ignore();
    }
}



