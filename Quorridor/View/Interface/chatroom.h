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

public:
    Chatroom(QWidget *parent=0);

    ~Chatroom();
    //crée l'introduction
    void setEntry();
    //crée l'affichage des messages
    void setDisplay();
    //récupère les messages de l'entrée
    QString getMessage();

public slots:
    //récupère les messages dans l'entré et les affiche
    void runChatroom();
};

#endif // CHATROOM_H
