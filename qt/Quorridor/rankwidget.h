#ifndef RANKWIDGET_H
#define RANKWIDGET_H

#include <QtWidgets>

class RankWidget : public QWidget
{
    QLabel *intro;
public:
    RankWidget(QWidget *parent=0);

    ~RankWidget();
};

#endif // RANKWIDGET_H
