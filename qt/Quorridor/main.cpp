#include <QtWidgets>

#include "login.h"

int main(int argv, char *args[])
{
    QApplication app(argv, args);
    Login loginWindow;
    loginWindow.show();
    return app.exec();
}

