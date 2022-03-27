#ifndef WALLCELL_H
#define WALLCELL_H

#include <QWidget>
#include <QFrame>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

//! [0]
class WallCell : public QWidget
{
    bool acceptDrop;
    bool receivedItem = false;


public:
    explicit WallCell(bool acceptDrop, QWidget *parent = nullptr);

    bool hasItem() {return receivedItem;}
    void setItem() {receivedItem = true;}

    void setWall() {
        this->setStyleSheet("background-color: black;");
}

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

};

#endif // WALLCELL_H
