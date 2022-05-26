#include "chatroom.h"

Chatroom::Chatroom(QWidget *parent) : QWidget(parent)
{
    chatroom = new QVBoxLayout(this);
    setDisplay();
    chatroom->addWidget(display);
    setEntry();
    chatroom->addWidget(entry);
}

Chatroom::~Chatroom() {
    delete chatroom;
    delete entry;
    delete display;
}

void Chatroom::setEntry() {
    entry = new QLineEdit();
    entry->setMinimumSize(QSize(200,30));
    entry->setStyleSheet("border: 1px solid black;");
    //quand la touche enter est pressée, la fonction runChatroom est appelée
    connect(entry,SIGNAL(returnPressed()), this, SLOT(runChatroom()));
}

void Chatroom::setDisplay() {
    display = new QTextEdit();
    display->setReadOnly(true);
    display->setMinimumSize(200, 150);
    display->setStyleSheet("border: 1px solid black; background-color : white;");
}

void Chatroom::runChatroom() {
    QString message = getMessage();
    display->append(message);
}

QString Chatroom::getMessage() {
    QString message = entry->text();
    entry->clear();
    return message;
}
