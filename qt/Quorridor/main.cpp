#include <QtWidgets>

#include "login.h"

int main(int argv, char *args[])
{
    QApplication app(argv, args);
    Start startWindow;
    startWindow.show();
    return app.exec();
}

