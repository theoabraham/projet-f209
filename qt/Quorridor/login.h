#include <QtWidgets>
#include "menuwindow.h"

#ifndef LOGIN_H
#define LOGIN_H

class Login : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout *loginLayout;
    QLabel *intro;
    QFormLayout *entry;
    QLineEdit *lpseudoLine;
    QLineEdit *lpasswordLine;
    QPushButton *connection;
    MenuWindow *menu;

public:
    Login(QWidget *parent=0);

    ~Login();

    void setIntro();

    void setEntry();

    void setConnection();


public slots:
    void launchMenu(); //TODO bouger dans public
    void checkPassword();
};

#endif // LOGIN_H


#ifndef SIGNUP_H
#define SIGNUP_H

class SignUp : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout *signUpLayout;
    QFormLayout *sEntry;
    QLineEdit *sPseudoLine;
    QLineEdit *sPasswordLine;
    QLineEdit *confPasswordLine;
    QLabel *pswReq;
    QPushButton *create;

public:
    SignUp(QWidget *parent=0);

    ~SignUp();

public slots:
    void backToStart();
};

#endif // SIGNUP_H

#ifndef START_H
#define START_H

class Start : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout *startLayout;
    QLabel *welcome;
    QLabel *instruction;
    QPushButton *loginButton;
    QPushButton *signUpButton;
    Login *logWindow;
    SignUp *suWindow;

public:
    Start(QWidget *parent=0);

public slots:
    void loginWindow();

    void signUpWindow();
};

#endif //START_H

