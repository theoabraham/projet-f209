#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>

class Window : public QWidget
{
    QGridLayout *boardGUI;

    QLabel *label;
    QLabel *label2;
    QLabel *label3;

public:
    Window(QWidget *parent=0);

    void resetVar();

    void boardGame();
};


#endif // WINDOW_H
