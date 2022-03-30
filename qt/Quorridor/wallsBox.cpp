#include <QtWidgets>
#include <iostream>
#include "wallsBox.h"


WallsBox::WallsBox(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(200, 200);
    setAcceptDrops(false);

    murH= new QLabel(this);
    murH->setPixmap(QPixmap(":/images/murH.jpg"));
    murH->move(30, 50);
    murH->show();
    murH->setAttribute(Qt::WA_DeleteOnClose);

    murV = new QLabel(this);
    murV->setPixmap(QPixmap(":/images/murV.jpg"));
    murV->move(5, 25);
    murV->show();
    murV->setAttribute(Qt::WA_DeleteOnClose);
}

WallsBox::~WallsBox(){
    delete murH;
    delete murV;
}

std::string WallsBox:: getTypeOfWall(){
    return wallType;
}

void WallsBox::setTypeOfWall(QLabel *wall){
    if (wall == murH){
        wallType = "H";
    }
    else if (wall == murV){
        wallType = "V";
    }
}

void WallsBox::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    setTypeOfWall(child);
    std::cout<<getTypeOfWall()<<std::endl;

    QPixmap pixmap = *child->pixmap();

    QByteArray itemData;

    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

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
