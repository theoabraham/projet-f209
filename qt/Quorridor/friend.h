#ifndef FRIEND_H
#define FRIEND_H

#include <QtWidgets>
#include "chatroom.h"

class Friend : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout *actions;
    QLabel *nameLabel;
    QLabel *rankLabel;
    QPushButton *messageButton;
    QPushButton *unfriendButton;
    Chatroom *privateChat;

public:
    Friend(QString name, QString rank, QWidget *parent=0);

public slots:
    void openChat();

    void unfriendRequested();
};

#endif // FRIEND_H
