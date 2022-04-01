#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QtWidgets>
#include "gamewindow.h"
#include "friendlistwidget.h"
#include "rankwidget.h"
#include "login.h"

class ClientGUI;

class MenuWindow : public QMainWindow
{
    Q_OBJECT

private:
    ClientGUI *client;

    //MenuWindow widgets
    QTabWidget *menuSelection;
    Login *login;
    SignUp *signUp;
    QWidget *play;
    QWidget *currentPlay;
    QWidget *lobby;
    FriendListWidget *friends;
    RankWidget *ranking;

    //Play widgets
    QVBoxLayout *playLayout;
    QLabel *playIntro;
    QGridLayout *options;
    QLabel *modeTitle;
    QComboBox *modeChoice;
    QLabel *playersTitle;
    QComboBox *playersChoice;
    QPushButton *startButton;

    //NewGame widgets
    QHBoxLayout *newGameLayout;
    GameWindow *game;
    bool gameStarted=false;

    //Join widgets
    QVBoxLayout *joinLayout;
    QLabel *lobbyIntro;
    QHBoxLayout *row;
    QLabel *lobbyNb;
    QPushButton *joinButton;

public:
    MenuWindow(ClientGUI *client, QMainWindow *parent=0);
    // Crée les éléments de l'onglet New game
    void setStart();
    // Crée les éléments de l'onglet Join game
    void setJoin();

public slots:
    // Lance une nouvelle partie
    void startGame();
    //Rejoins une partie déjà existante
    void joinGame();
    // Affiche le menu après la connexion
    void launchMenu();
    // Crée un compte
    void createAccount();
    // Quitte une partie et donne la possibilité de sauvegarder ou non
    void leaveAndSave();
};

#endif // MENUWINDOW_H
