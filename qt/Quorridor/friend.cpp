#include "friend.h"

Friend::Friend(QWidget *parent) : QWidget(parent)
{
    actions = new QVBoxLayout(this);
    name = new QLabel("Pseudo");
    actions->addWidget(name);
    rank = new QLabel("Rank #2");
    actions->addWidget(rank);
    messageButton = new QPushButton("Message");
    connect(messageButton, SIGNAL(clicked()), this, SLOT(openChat()));
    actions->addWidget(messageButton);
    unfriendButton = new QPushButton("Unfriend");
    connect(unfriendButton, SIGNAL(clicked()), this, SLOT(unfriendRequested()));
    actions->addWidget(unfriendButton);
}

void Friend::openChat() {
    privateChat = new Chatroom();
    privateChat->show();
}

void Friend::unfriendRequested() {
    unfriendButton->setText("Add friend");
}
