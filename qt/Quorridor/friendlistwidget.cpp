#include "friendlistwidget.h"

FriendListWidget::FriendListWidget(QWidget *parent): QWidget(parent)
{
    friendLayout = new QHBoxLayout(this);
    setIntro();
    friendLayout->addWidget(intro);
    //setFriends();
}

FriendListWidget::~FriendListWidget() {
    delete intro;
    delete friendLayout;
    /*for (int i=0; i<3;i++) {
        delete friendsList[i];
    }*/
}

void FriendListWidget::setIntro() {
    intro = new QLabel(this);
    intro->setText("Here is your friends' list: ");
    intro->setFont(QFont("Arial", 14, QFont::Bold));
}

void FriendListWidget::setFriends() {
    /*for (long unsigned int i=0; i<3;i++) {
        friendsList[i] = new Friend();
        friendLayout->addWidget(friendsList[i]);
    }*/
    return;
}
