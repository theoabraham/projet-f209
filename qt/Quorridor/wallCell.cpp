#include <QtWidgets>
#include <iostream>
#include "wallCell.h"

WallCell::WallCell(QWidget *parent)
    : QWidget (parent)
{
    //setMinimumSize(200, 200);
    setAcceptDrops(true);
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
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(10,10);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        event->acceptProposedAction();

        receivedItem = true;

    } else {
        event->ignore();
    }

}
