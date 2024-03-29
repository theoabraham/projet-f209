#include "pawncell.h"

PawnCell::PawnCell(WallsBox *wall, QWidget *parent)
    : QWidget(parent), wall(wall)
{
    setAcceptDrops(true);
    setStyleSheet("background-color: brown;");
}

void PawnCell::setImage(QPixmap pix){
    pawn = new QLabel(this);
    pawn->setPixmap(pix);
    pawn->move(0,0);
    pawn->show();
    pawn->setAttribute(Qt::WA_DeleteOnClose);
}

void PawnCell::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void PawnCell::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        if (event->source() != wall){

                QPixmap pixmap;
                QPoint offset;
                dataStream >> pixmap >> offset;

                QLabel *newIcon = new QLabel(this);
                newIcon->setPixmap(pixmap);
                newIcon->move(0,0);
                newIcon->show();
                newIcon->setAttribute(Qt::WA_DeleteOnClose);

                if (event->source() != this) {
                    event->setDropAction(Qt::MoveAction);
                    event->accept();
                } else {
                    event->acceptProposedAction();
                }            
        }
    } else {
            event->ignore();
        }


}

void PawnCell::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

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
