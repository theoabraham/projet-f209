#ifndef FRIEND_H
#define FRIEND_H

#include <QtWidgets>

class Friend : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *actions;
    QLabel *nameLabel;
    QLabel *rankLabel;
    QPushButton *button;

public:
    Friend(bool isFriend, QString name="name", QString rank="n", QWidget *parent=0);

    ~Friend();

    void setButton(bool isFriend);

public slots:
    void friendRequested();
};

#endif // FRIEND_H
