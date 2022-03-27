#ifndef WALLSBOX_H
#define WALLSBOX_H

#include <QtWidgets>
#include <QFrame>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE


class WallsBox : public QWidget
{
public:
    explicit WallsBox(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // WALLSBOX_H
