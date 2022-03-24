#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>

class Window : public QWidget
{
    QVBoxLayout *mainLayout;
    QGridLayout *boardGUI;
    QHBoxLayout *wallsPlacement;

    QLabel *label;
    QLabel *label2;
    QLabel *label3;
    QLabel *murH;
    QLabel *murV;

public:
    Window(QWidget *parent=0);

    void resetVar();

    void boardGame();

    void wallSelection();
};


#endif // WINDOW_H
