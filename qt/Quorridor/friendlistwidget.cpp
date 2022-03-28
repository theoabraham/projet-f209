#include "friendlistwidget.h"

FriendListWidget::FriendListWidget(QWidget *parent): QWidget(parent)
{
    friendLayout = new QVBoxLayout(this);
    setIntro();
    friendLayout->addWidget(intro);
    setFriends();
    friendLayout->addStretch();
}

FriendListWidget::~FriendListWidget() {
    delete intro;
    delete friendLayout;
    for (unsigned long int i=0; i<friendsList.size();i++) {
        delete friendsList[i];
    }
}

void FriendListWidget::setIntro() {
    intro = new QLabel(this);
    intro->setText("Here is your friends' list: ");
    intro->setFont(QFont("Arial", 14, QFont::Bold));
}

void FriendListWidget::setFriends() {
    addFriend(QString("Jean"), QString("2"));
    addFriend(QString("Charles"), QString("3"));
    for (long unsigned int i=0; i<friendsList.size();i++) {
        friendLayout->addWidget(friendsList[i]);
    }
}

void FriendListWidget::addFriend(QString name, QString rank) {
    Friend *newFriend = new Friend(name, rank);
    friendsList.push_back(newFriend);
}
