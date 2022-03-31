#include <QtWidgets>

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

public:
    Login(QWidget *parent=0);

    QPushButton* getConnection() {return connection;}

    void setIntro();

    void setEntry();

    void setConnection();

    bool checkPassword();
};

#endif // LOGIN_H


#ifndef SIGNUP_H
#define SIGNUP_H

class SignUp : public QWidget
{
    Q_OBJECT

private:
    QVBoxLayout *signUpLayout;
    QLabel *sIntro;
    QFormLayout *sEntry;
    QLineEdit *sPseudoLine;
    QLineEdit *sPasswordLine;
    QLineEdit *confPasswordLine;
    QLabel *pswReq;
    QPushButton *create;

public:
    SignUp(QWidget *parent=0);

    QPushButton* getCreate() {return create;}

    void setIntro();

    void setEntry();

    void setButton();
};

#endif // SIGNUP_H

