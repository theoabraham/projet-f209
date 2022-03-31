#ifndef FRIENDLISTWIDGET_H
#define FRIENDLISTWIDGET_H

#include <QtWidgets>
#include "friend.h"

class FriendListWidget : public QWidget
{
    QVBoxLayout *friendLayout;
    QLabel *intro;
    std::vector<Friend*> friendsList;
public:
    FriendListWidget(QWidget *parent=0);

    ~FriendListWidget();

    void setIntro();

    void setFriends();

    void addFriend(QString name, QString rank);
};

#endif // FRIENDLISTWIDGET_H
