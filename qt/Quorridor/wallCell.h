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
    bool receivedItem = false;
public:
    explicit WallCell(QWidget *parent = nullptr);

protected:
    //S'occupe de reconnaitre l'item qui rentre dans son widget
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};

#endif // WALLCELL_H
