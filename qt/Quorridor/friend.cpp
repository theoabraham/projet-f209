#include "friend.h"

Friend::Friend(QString name, QString rank, QWidget *parent) : QWidget(parent)
{
    actions = new QHBoxLayout(this);
    nameLabel = new QLabel(name);
    actions->addWidget(nameLabel);
    rankLabel = new QLabel("Rank #"+rank);
    actions->addWidget(rankLabel);
    messageButton = new QPushButton("Message");
    connect(messageButton, SIGNAL(clicked()), this, SLOT(openChat()));
    actions->addWidget(messageButton);
    unfriendButton = new QPushButton("Unfriend");
    connect(unfriendButton, SIGNAL(clicked()), this, SLOT(unfriendRequested()));
    actions->addWidget(unfriendButton);
}

void Friend::openChat() {
    privateChat = new Chatroom(nameLabel->text());
    privateChat->show();
}

void Friend::unfriendRequested() {
    unfriendButton->setText("Add friend");
}
