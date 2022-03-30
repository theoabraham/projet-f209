#include "menuwindow.h"
#include "gamewindow.h"

MenuWindow::MenuWindow(QMainWindow *parent): QMainWindow(parent)
{
    setWindowTitle("Quoridor");
    setMinimumSize(900,700);

    menuSelection = new QTabWidget();
    menuSelection->resize(sizeHint());

    login = new Login();
    connect(login->getConnection(), SIGNAL(clicked()), this, SLOT(launchMenu()));
    menuSelection->addTab(login, "Login");

    signUp = new SignUp();
    connect(signUp->getCreate(), SIGNAL(clicked()), this, SLOT(createAccount()));
    menuSelection->addTab(signUp, "Sign up");

    setCentralWidget(menuSelection);
}

void MenuWindow::setStart() {
    playLayout = new QVBoxLayout(play);

    playIntro = new QLabel("Choose your game's options");
    playIntro->setFont(QFont("Arial", 14, QFont::Bold));
    playIntro->setAlignment(Qt::AlignHCenter);
    playLayout->addWidget(playIntro);

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

    startButton = new QPushButton("Start");
    connect(startButton, SIGNAL(clicked()), this, SLOT(startGame()));
    playLayout->addWidget(startButton);
    playLayout->addStretch();
}

void MenuWindow::setJoin() {
    joinLayout = new QVBoxLayout(lobby);

    lobbyIntro = new QLabel("Here are the lobbys open");
    lobbyIntro->setFont(QFont("Arial", 14, QFont::Bold));
    lobbyIntro->setAlignment(Qt::AlignHCenter);
    joinLayout->addWidget(lobbyIntro);

    row = new QHBoxLayout();
    lobbyNb = new QLabel("Lobby #1");
    row->addWidget(lobbyNb);
    joinButton = new QPushButton("Join");
    connect(joinButton, SIGNAL(clicked()), this, SLOT(joinGame()));
    row->addWidget(joinButton);
    joinLayout->addLayout(row);
    joinLayout->addStretch();
}

void MenuWindow::startGame() {
    std::string mode = modeChoice->currentText().toStdString();
    std::string nbPlayers = playersChoice->currentText().toStdString();
    //TODO impliquer dans la construction de gamewindow
    newGameLayout = new QHBoxLayout(currentPlay);
    game = new GameWindow();
    newGameLayout->addWidget(game);
    menuSelection->setTabEnabled(1, true);
    menuSelection->setTabEnabled(0, false);
}

void MenuWindow::joinGame() {
    newGameLayout->removeWidget(game);
    game = new GameWindow();
    newGameLayout->addWidget(game);
    menuSelection->setCurrentIndex(1);
    menuSelection->setTabEnabled(1,true);
    menuSelection->setTabEnabled(0, false);
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
    //TODO créer un compte dans la DB
    menuSelection->setCurrentIndex(0);
}
