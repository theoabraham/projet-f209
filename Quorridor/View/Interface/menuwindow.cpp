#include "menuwindow.h"
#include "gamewindow.h"

MenuWindow::MenuWindow(ClientGUI *client, QMainWindow *parent): QMainWindow(parent), client{client}
{
    setWindowTitle("Quoridor");
    setMinimumSize(900,700);

    menuSelection = new QTabWidget();
    menuSelection->resize(sizeHint());
    //Onglet Login
    login = new Login();
    connect(login->getConnection(), SIGNAL(clicked()), this, SLOT(launchMenu()));
    menuSelection->addTab(login, "Login");
    //Onglet Sign up
    signUp = new SignUp();
    connect(signUp->getCreate(), SIGNAL(clicked()), this, SLOT(createAccount()));
    menuSelection->addTab(signUp, "Sign up");

    setCentralWidget(menuSelection); //permet la redimension de la fenetre
}

void MenuWindow::setStart() {
    playLayout = new QVBoxLayout(play);
    //Introduction
    playIntro = new QLabel("Choose your game's options");
    playIntro->setFont(QFont("Arial", 14, QFont::Bold));
    playIntro->setAlignment(Qt::AlignHCenter);
    playLayout->addWidget(playIntro);
    //Options de jeu
    options = new QGridLayout();
    modeTitle = new QLabel("Game mode");
    options->addWidget(modeTitle, 0, 0);
    modeChoice = new QComboBox();
    modeChoice->addItem("ClassiQ");
    modeChoice->addItem("DestruQtion");
    modeChoice->addItem("QQQuoridor");
    modeChoice->addItem("Minos");
    options->addWidget(modeChoice, 0, 1);
    playersTitle = new QLabel("Number of players");
    options->addWidget(playersTitle, 1, 0);
    playersChoice = new QComboBox();
    playersChoice->addItem("2");
    playersChoice->addItem("4");
    options->addWidget(playersChoice, 1, 1);
    playLayout->addLayout(options);
    //Bouton start
    startButton = new QPushButton("Start");
    //connecte le bouton start à la fonction startGame
    connect(startButton, SIGNAL(clicked()), this, SLOT(startGame()));
    playLayout->addWidget(startButton);
    playLayout->addStretch();
}

void MenuWindow::setJoin() {
    joinLayout = new QVBoxLayout(lobby);
    //Introduction
    lobbyIntro = new QLabel("Here are the lobbys open");
    lobbyIntro->setFont(QFont("Arial", 14, QFont::Bold));
    lobbyIntro->setAlignment(Qt::AlignHCenter);
    joinLayout->addWidget(lobbyIntro);
    //Un salon
    row = new QHBoxLayout();
    lobbyNb = new QLabel("Lobby #1");
    row->addWidget(lobbyNb);
    joinButton = new QPushButton("Join");
    //connecte le bouton Join à la fonction joinGame
    connect(joinButton, SIGNAL(clicked()), this, SLOT(joinGame()));
    row->addWidget(joinButton);
    joinLayout->addLayout(row);

    joinLayout->addStretch();
}

void MenuWindow::startGame() {
    if (gameStarted) {
        menuSelection->removeTab(1);
        currentPlay = new QWidget;
        menuSelection->insertTab(1,currentPlay, "Current Game");
    }
    std::string mode = modeChoice->currentText().toStdString();
    std::string nbPlayers = playersChoice->currentText().toStdString();
    newGameLayout = new QHBoxLayout(currentPlay);
    game= new GameWindow(client);
    //connecte le bouton Quit and Save à la fonction leaveAndSave
    connect(game->getLeaveButton(), SIGNAL(clicked()), this, SLOT(leaveAndSave()));
    newGameLayout->addWidget(game);
    menuSelection->setTabEnabled(1, true);
    menuSelection->setTabEnabled(0, false);
    gameStarted = true;
}

void MenuWindow::joinGame() {
    if (gameStarted) {
        QMessageBox changeGame;
        changeGame.setText("Do you really want to leave the current game to this lobby's game ?");
        changeGame.setIcon(QMessageBox::Question);
        changeGame.setWindowTitle("Leave current game");
        changeGame.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        int leave = changeGame.exec();
        switch (leave) {
        case QMessageBox::Yes:
            menuSelection->removeTab(1);
            currentPlay = new QWidget;
            menuSelection->insertTab(1,currentPlay, "Current Game");
            startGame();
            menuSelection->setCurrentIndex(1);
            break;
        case QMessageBox::No:
            break;
        default:
            break;
        }
    }
    else {
        startGame();
        menuSelection->setCurrentIndex(1);
    }
}

void MenuWindow::leaveAndSave() {
    QMessageBox confirmation;
    confirmation.setText("Do you really want to quit ?");
    confirmation.setWindowTitle("Are you sure ?");
    confirmation.setIcon(QMessageBox::Question);
    confirmation.setStandardButtons(QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
    int choice = confirmation.exec();
    switch (choice) {
    case QMessageBox::Discard:
        menuSelection->setCurrentIndex(0);
        menuSelection->removeTab(1);
        currentPlay = new QWidget;
        menuSelection->insertTab(1,currentPlay, "Current Game");
        menuSelection->setTabEnabled(0, true);
        menuSelection->setTabEnabled(1, false);
        gameStarted = false;
        break;
    case QMessageBox::Cancel:
        break;
    case QMessageBox::Save:
        menuSelection->removeTab(1);
        currentPlay = new QWidget;
        menuSelection->insertTab(1,currentPlay, "Current Game");
        startGame();
        menuSelection->setTabEnabled(0, true);
        menuSelection->setTabEnabled(1, false);
        menuSelection->setCurrentIndex(0);
        break;
    default:
        break;
    }
}

void MenuWindow::launchMenu() {
    if (login->checkPassword()) {
        menuSelection->removeTab(1);
        menuSelection->removeTab(0);

        play = new QWidget();
        setStart();
        menuSelection->addTab(play, "New Game");

        currentPlay = new QWidget();
        menuSelection->addTab(currentPlay, "Current Game");
        menuSelection->setTabEnabled(1, false);

        lobby = new QWidget();
        setJoin();
        menuSelection->addTab(lobby, "Join Lobby");

        friends = new FriendListWidget();
        menuSelection->addTab(friends, "Friends");

        ranking = new RankWidget();
        menuSelection->addTab(ranking, "Ranking");
    }
}

void MenuWindow::createAccount() {
    menuSelection->setCurrentIndex(0);
}
