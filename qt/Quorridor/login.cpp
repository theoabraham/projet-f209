#include "login.h"
#include "menuwindow.h"

Login::Login(QWidget *parent) : QWidget(parent)
{
    loginLayout = new QVBoxLayout(this);
    setIntro();
    loginLayout->addWidget(intro);
    setEntry();
    loginLayout->addLayout(entry);
    setConnection();
    loginLayout->addWidget(connection);
}

Login::~Login() {
    delete loginLayout;
    delete intro;
    delete entry;
    delete pseudoLine;
    delete passwordLine;
    delete connection;
    delete menu;
}

void Login::setIntro() {
    intro = new QLabel("Welcome to Quoridor ! \nLogin to access the game");
    intro->setFont(QFont("Arial", 14, QFont::Bold));
}

void Login::setEntry() {
    entry = new QFormLayout();
    pseudoLine = new QLineEdit();
    passwordLine = new QLineEdit();
    passwordLine->setEchoMode(QLineEdit::Password);
    entry->addRow(new QLabel("Pseudo"), pseudoLine);
    entry->addRow(new QLabel("Password"), passwordLine);
}

void Login::setConnection() {
    connection = new QPushButton("LOGIN");
    connect(connection, SIGNAL(clicked()), this, SLOT(launchMenu()));
}

void Login::launchMenu() {
    menu = new MenuWindow();
    menu->show();
    hide();
}
