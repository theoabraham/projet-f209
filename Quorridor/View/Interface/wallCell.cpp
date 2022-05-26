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
        //Si la souris à est entrain de drag sur un item de type image 
        if (event->source() != this) {
            //Si l'endroit d'où vient la souris viens d'un autre widget
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
        //Si l'élément qui va être drop est de type image
        if (event->source() == wall){
            //Si l'item qui est drag viens de WallsBox

            event->acceptProposedAction();

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