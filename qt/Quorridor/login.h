#ifndef LOGIN_H
#define LOGIN_H

#include <QtWidgets>
#include "menuwindow.h"

class Login : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout *loginLayout;
    QLabel *intro;
    QFormLayout *entry;
    QLineEdit *pseudoLine;
    QLineEdit *passwordLine;
    QPushButton *connection;
    MenuWindow *menu;

public:
    Login(QWidget *parent=0);

    ~Login();

    void setIntro();

    void setEntry();

    void setConnection();

public slots:
    void launchMenu();

};

#endif // LOGIN_H
