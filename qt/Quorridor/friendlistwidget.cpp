#include "friendlistwidget.h"

FriendListWidget::FriendListWidget(QWidget *parent): QWidget(parent)
{
    intro = new QLabel(this);
    intro->setText("Here is your friends' list: ");
    intro->setFont(QFont("Arial", 14, QFont::Bold));
}
