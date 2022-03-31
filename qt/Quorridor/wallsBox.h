#ifndef WALLSBOX_H
#define WALLSBOX_H

#include <QtWidgets>
#include <QFrame>
#include <string>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE


class WallsBox : public QWidget
{
    QLabel *murH;
    QLabel *murV;

    std::string wallType;
public:
    explicit WallsBox(QWidget *parent = nullptr);
    ~WallsBox();
    void setTypeOfWall(QLabel *wall);
    std::string getTypeOfWall();

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // WALLSBOX_H
