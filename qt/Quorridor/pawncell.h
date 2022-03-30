#ifndef PAWNCELL_H
#define PAWNCELL_H

#include <QtWidgets>
#include <string>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE


class PawnCell: public QWidget
{
    QLabel *pawn;
public:
    explicit PawnCell(QWidget *parent = nullptr);

    void setImage(QPixmap pix);
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    //void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // PAWNCELL_H

