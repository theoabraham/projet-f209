#ifndef FRIENDLISTWIDGET_H
#define FRIENDLISTWIDGET_H

#include <QtWidgets>
#include "friend.h"

class FriendListWidget : public QWidget
{
    QHBoxLayout *friendLayout;
    QLabel *intro;
    std::vector<Friend*> friendsList[3];
public:
    FriendListWidget(QWidget *parent=0);

    ~FriendListWidget();

    void setIntro();

    void setFriends();
};

#endif // FRIENDLISTWIDGET_H
