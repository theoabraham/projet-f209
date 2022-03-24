#include <QtWidgets>

#include "window.h"

int main(int argv, char *args[])
{
    QApplication app(argv, args);
    Window window;
    window.setFixedSize(500,700);
    window.show();
    return app.exec();
}

