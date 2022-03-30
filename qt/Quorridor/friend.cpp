#include "friend.h"

Friend::Friend(bool isFriend, QString name, QString rank, QWidget *parent) : QWidget(parent)
{
    actions = new QHBoxLayout(this);
    nameLabel = new QLabel(name);
    actions->addWidget(nameLabel);
    rankLabel = new QLabel("Rank #"+rank);
    actions->addWidget(rankLabel);
    setButton(isFriend);
    actions->addWidget(button);
}

Friend::~Friend() {
    delete actions;
    delete nameLabel;
    delete rankLabel;
    delete button;
}

void Friend::setButton(bool isFriend) {
    if (isFriend) {
        button = new QPushButton("Unfriend");
    }
    else {
        button = new QPushButton("Add friend");
    }
    connect(button, SIGNAL(clicked()), this, SLOT(friendRequested()));
}

void Friend::friendRequested() {
    if (button->text() == "Add friend") {
        button->setText("Unfriend");
    }
    else {
        button->setText("Add friend");
    }
}
