#include <QtWidgets>
#include <iostream>
#include "wallsBox.h"


WallsBox::WallsBox(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(200, 200);
    setAcceptDrops(false);

    QLabel *murH= new QLabel(this);
    murH->setPixmap(QPixmap(":/images/murH.jpg"));
    murH->move(30, 10);
    murH->show();
    murH->setAttribute(Qt::WA_DeleteOnClose);


    QLabel *murV = new QLabel(this);
    murV->setPixmap(QPixmap(":/images/murV.jpg"));
    murV->move(10, 10);
    murV->show();
    murV->setAttribute(Qt::WA_DeleteOnClose);
}

void WallsBox::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->position().toPoint()));
    if (!child)
        return;

    QPixmap pixmap = child->pixmap(Qt::ReturnByValue);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->position().toPoint() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->position().toPoint() - child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}
