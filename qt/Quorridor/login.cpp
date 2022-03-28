#include "login.h"
#include "menuwindow.h"

Login::Login(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Quoridor - Login");

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
    delete lpseudoLine;
    delete lpasswordLine;
    delete connection;
    delete menu;
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
    lpasswordLine->setEchoMode(QLineEdit::Password);
    entry->addRow(new QLabel("Password"), lpasswordLine);
}

void Login::setConnection() {
    connection = new QPushButton("Login");
    connect(connection, SIGNAL(clicked()), this, SLOT(launchMenu()));
    //connect(connection, SIGNAL(clicked()), this, SLOT(checkPassword()));
}

void Login::launchMenu() {
    menu = new MenuWindow();
    menu->show();
    close();
}

void Login::checkPassword() {
    std::string pseudo = lpseudoLine->text().toStdString();
    std::string password = lpasswordLine->text().toStdString();
    //TODO connexion avec la base de données via le client
    /* if pseudo ok && password ok
          launchMenu();
    */
}

SignUp::SignUp(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Quoridor - Sign Up");

    signUpLayout = new QVBoxLayout(this);

    sEntry = new QFormLayout();
    sPseudoLine = new QLineEdit();
    sEntry->addRow(new QLabel("Enter Pseudo"), sPseudoLine);
    sPasswordLine = new QLineEdit();
    sPasswordLine->setEchoMode(QLineEdit::Password);
    sEntry->addRow(new QLabel("Enter Password"), sPasswordLine);
    confPasswordLine = new QLineEdit();
    confPasswordLine->setEchoMode(QLineEdit::Password);
    sEntry->addRow(new QLabel("Confirm  Password"), confPasswordLine);
    signUpLayout->addLayout(sEntry);

    pswReq = new QLabel("Must be between 3 and 16 caracters\nCan't contain spaces");
    signUpLayout->addWidget(pswReq);

    create = new QPushButton("Create an account");
    connect(create, SIGNAL(clicked()), this, SLOT(backToStart()));
    signUpLayout->addWidget(create);
    signUpLayout->addStretch();
}

SignUp::~SignUp() {
    delete signUpLayout;
    delete sEntry;
    delete sPseudoLine;
    delete sPasswordLine;
    delete confPasswordLine;
    delete pswReq;
    delete create;
}

void SignUp::backToStart() {
    // TODO check compte valable et le créer
    close();
}

Start::Start(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Quoridor - Welcome");

    startLayout = new QVBoxLayout(this);
    welcome = new QLabel("Welcome to Quoridor");
    welcome->setFont(QFont("Arial", 14, QFont::Bold));
    welcome->setAlignment(Qt::AlignHCenter);
    startLayout->addWidget(welcome);

    loginButton = new QPushButton("Login");
    connect(loginButton, SIGNAL(clicked()), this, SLOT(loginWindow()));
    startLayout->addWidget(loginButton);

    instruction = new QLabel("If you don't have an account yet, Sign Up.");
    instruction->setAlignment(Qt::AlignHCenter);
    startLayout->addWidget(instruction);
    signUpButton = new QPushButton("Sign Up");
    connect(signUpButton, SIGNAL(clicked()), this, SLOT(signUpWindow()));
    startLayout->addWidget(signUpButton);
}

void Start::loginWindow() {
    logWindow = new Login();
    logWindow->show();
    close();
}

void Start::signUpWindow() {
    suWindow = new SignUp();
    suWindow->show();
}
