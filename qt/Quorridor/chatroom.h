#ifndef CHATROOM_H
#define CHATROOM_H

#include <QtWidgets>

class Chatroom : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *chatroom;
    QLineEdit *entry;
    QTextEdit *display;
    QLabel *title;

public:
    Chatroom(QString friendName="Chatroom",QString windowTitle="Quoridor - Private Chatroom", QWidget *parent=0);

    ~Chatroom();

    void setEntry();

    void setDisplay();

    void setTitle(QString friendName);

    QString getMessage();

public slots:
    void runChatroom();
};

#endif // CHATROOM_H
