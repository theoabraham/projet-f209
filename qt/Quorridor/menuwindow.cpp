#include "menuwindow.h"
#include "gamewindow.h"

MenuWindow::MenuWindow(QMainWindow *parent): QMainWindow(parent)
{
    setWindowTitle("Quoridor - Menu");
    setMinimumSize(500,150);

    menuSelection = new QTabWidget();
    menuSelection->setMinimumSize(sizeHint());

    play = new QWidget();
    setStart();
    menuSelection->addTab(play, "New Game");

    lobby = new QWidget();
    setJoin();
    menuSelection->addTab(lobby, "Join Lobby");

    friends = new FriendListWidget();
    menuSelection->addTab(friends, "Friends");

    ranking = new RankWidget();
    menuSelection->addTab(ranking, "Ranking");
    setCentralWidget(menuSelection);
}

MenuWindow::~MenuWindow() {
    delete menuSelection;
    delete play;
    delete lobby;
    delete friends;
    delete ranking;

    delete playLayout;
    delete playIntro;
    delete options;
    delete modeTitle;
    delete modeChoice;
    delete playersTitle;
    delete playersChoice;
    delete startButton;
    delete game;

    delete joinLayout;
    delete lobbyIntro;
    delete rowLobby;
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

    rowLobby = new LobbyWidget();
    joinLayout->addWidget(rowLobby);
    joinLayout->addStretch();
}

void MenuWindow::startGame() {
    std::string mode = modeChoice->currentText().toStdString();
    std::string nbPlayers = playersChoice->currentText().toStdString();
    //TODO impliquer dans la construction de gamewindow
    game = new GameWindow();
    game->show();
}
