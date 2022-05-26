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
    //Crée les éléments de l'introduction
    void setIntro();
    //crée le formulaire pour entrer le pseudo et le mot de passe
    void setEntry();
    //crée le bouton pour se connecter
    void setConnection();
    // vérifie que le mot de passe est correct
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
    //Crée les éléments de l'introduction
    void setIntro();
    //crée le formulaire pour entrer le pseudo et le mot de passe et sa confirmation
    void setEntry();
    //crée le bouton pour créer un compte
    void setButton();
};

#endif // SIGNUP_H

