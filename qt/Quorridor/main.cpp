#include <QtWidgets>

#include "window.h"

int main(int argv, char *args[])
{
    QApplication app(argv, args);
    Window window;
    window.setFixedSize(500,500);
    window.show();
    return app.exec();
}

/*
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
*/
