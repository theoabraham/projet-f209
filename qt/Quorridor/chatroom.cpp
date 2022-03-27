#include "chatroom.h"

Chatroom::Chatroom(QWidget *parent) : QWidget(parent)
{
    chatroom = new QVBoxLayout(this);
    setTitle();
    chatroom->addWidget(title);
    setDisplay();
    chatroom->addWidget(display);
    setEntry();
    chatroom->addWidget(entry);
}

Chatroom::~Chatroom() {
    delete chatroom;
    delete entry;
    delete display;
    delete title;
}

void Chatroom::setEntry() {
    entry = new QLineEdit();
    entry->setMinimumSize(QSize(250,50));
    entry->setStyleSheet("border: 1px solid black;");
    connect(entry,SIGNAL(returnPressed()), this, SLOT(runChatroom()));
}

void Chatroom::setDisplay() {
    display = new QTextEdit();
    display->setReadOnly(true);
    display->setMinimumSize(QSize(250,530));
    display->setStyleSheet("border: 1px solid black; background-color : white;");
}

void Chatroom::setTitle() {
    title = new QLabel("Chatroom");
    title->setIndent(80);
    title->setFont(QFont("Arial", 14, QFont::Bold));
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
