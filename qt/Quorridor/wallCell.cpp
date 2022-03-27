#include <QtWidgets>
#include <iostream>
#include "wallCell.h"

WallCell::WallCell(bool acceptDrop, QWidget *parent)
    : QWidget (parent), acceptDrop(acceptDrop)
{
    //setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
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

        this->setStyleSheet("background-color: black;");
        event->acceptProposedAction();
        receivedItem = true;
    } else {
        event->ignore();
    }

}

