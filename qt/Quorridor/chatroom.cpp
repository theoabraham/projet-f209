#include "chatroom.h"

Chatroom::Chatroom(QString friendName, QString windowTitle, QWidget *parent) : QWidget(parent)
{
    setWindowTitle(windowTitle);
    chatroom = new QVBoxLayout(this);
    setTitle(friendName);
    setDisplay();
    chatroom->addWidget(title);
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
    entry->setMinimumSize(QSize(200,30));
    entry->setStyleSheet("border: 1px solid black;");
    connect(entry,SIGNAL(returnPressed()), this, SLOT(runChatroom()));
}

void Chatroom::setDisplay() {
    display = new QTextEdit();
    display->setReadOnly(true);
    display->setMinimumSize(QSize(250,450));
    display->setStyleSheet("border: 1px solid black; background-color : white;");
}

void Chatroom::setTitle(QString friendName) {
    title = new QLabel(friendName);
    title->setAlignment(Qt::AlignHCenter);
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
