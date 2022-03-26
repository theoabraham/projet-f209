#ifndef FRIENDLISTWIDGET_H
#define FRIENDLISTWIDGET_H

#include <QtWidgets>

class FriendListWidget : public QWidget
{
    QLabel *intro;
public:
    FriendListWidget(QWidget *parent=0);
};

#endif // FRIENDLISTWIDGET_H
