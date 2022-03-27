#ifndef FRIEND_H
#define FRIEND_H

#include <QtWidgets>
#include "chatroom.h"

class Friend : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *actions;
    QLabel *name;
    QLabel *rank;
    QPushButton *messageButton;
    QPushButton *unfriendButton;
    Chatroom *privateChat;

public:
    Friend(QWidget *parent=0);

public slots:
    void openChat();

    void unfriendRequested();
};

#endif // FRIEND_H
