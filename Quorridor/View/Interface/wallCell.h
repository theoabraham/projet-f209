#ifndef WALLCELL_H
#define WALLCELL_H

#include <QWidget>
#include <vector>
#include <iostream>
#include "wallsBox.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class WallCell : public QWidget
{
    WallsBox *wall;

    bool acceptDrop;
    bool receivedItem = false;

    std::vector< WallCell *> vectMurH {nullptr, nullptr};
    std::vector< WallCell *> vectMurV {nullptr, nullptr};

public:
    explicit WallCell(bool acceptDrop, WallsBox *wall, QWidget *parent = nullptr);

    bool hasItem() {return receivedItem;}
    void setItem() {receivedItem = true;}

    void setWallColor() {this->setStyleSheet("background-color: black;");}
    void setVectMurH(std::vector< WallCell *> vect) {vectMurH = vect;}
    void setVectMurV(std::vector< WallCell *> vect) {vectMurV = vect;}

    std::vector< WallCell *> getvectH(){return vectMurH;}

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};

#endif // WALLCELL_H
