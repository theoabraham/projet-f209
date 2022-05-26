#include "login.h"

Login::Login(QWidget *parent) : QWidget(parent)
{
    loginLayout = new QVBoxLayout(this);
    setIntro();
    loginLayout->addWidget(intro);
    setEntry();
    loginLayout->addLayout(entry);
    setConnection();
    loginLayout->addWidget(connection);
    loginLayout->addStretch();
}

void Login::setIntro() {
    intro = new QLabel("Welcome to Quoridor !\nLogin to access the game");
    intro->setFont(QFont("Arial", 14, QFont::Bold));
    intro->setAlignment(Qt::AlignHCenter);
}

void Login::setEntry() {
    entry = new QFormLayout();
    lpseudoLine = new QLineEdit();
    entry->addRow(new QLabel("Pseudo"), lpseudoLine);
    lpasswordLine = new QLineEdit();
    lpasswordLine->setEchoMode(QLineEdit::Password);  //camoufle le mot de passe
    entry->addRow(new QLabel("Password"), lpasswordLine);
}

void Login::setConnection() {
    connection = new QPushButton("Login");
}

bool Login::checkPassword() {
    std::string pseudo = lpseudoLine->text().toStdString();
    std::string password = lpasswordLine->text().toStdString();
    return true;
}

SignUp::SignUp(QWidget *parent) : QWidget(parent) {
    signUpLayout = new QVBoxLayout(this);

    setIntro();
    signUpLayout->addWidget(sIntro);

    setEntry();
    signUpLayout->addLayout(sEntry);

    setButton();
    signUpLayout->addWidget(create);

    signUpLayout->addStretch();
}

void SignUp::setIntro() {
    sIntro = new QLabel("To create an account, enter a pseudo and a valid password");
    sIntro->setFont(QFont("Arial", 14, QFont::Bold));
}

void SignUp::setEntry() {
    sEntry = new QFormLayout();
    sPseudoLine = new QLineEdit();
    sEntry->addRow(new QLabel("Enter pseudo"), sPseudoLine);
    sPasswordLine = new QLineEdit();
    sPasswordLine->setEchoMode(QLineEdit::Password);
    sEntry->addRow(new QLabel("Enter password"), sPasswordLine);
    pswReq = new QLabel("Must be between 4 and 16 caracters\nCan't contain spaces");
    sEntry->addRow("", pswReq);
    confPasswordLine = new QLineEdit();
    confPasswordLine->setEchoMode(QLineEdit::Password);
    sEntry->addRow(new QLabel("Confirm  password"), confPasswordLine);
}

void SignUp::setButton() {
    create = new QPushButton("Create an account");
}
