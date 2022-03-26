#include "rankwidget.h"

RankWidget::RankWidget(QWidget *parent): QWidget(parent)
{
    intro = new QLabel(this);
    intro->setText("Your rank is #1");
    intro->setFont(QFont("Arial", 14, QFont::Bold));
}
