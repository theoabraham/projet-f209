#include "menuwindow.h"
#include "gamewindow.h"

MenuWindow::MenuWindow(QMainWindow *parent): QMainWindow(parent)
{
    setWindowTitle("Quoridor - Menu");
    setMinimumSize(500,200);
    menuSelection = new QTabWidget();
    menuSelection->setMinimumSize(QSize(500,200));
    play = new QWidget();
    setStart();
    menuSelection->addTab(play, "Play");
    friends = new FriendListWidget();
    menuSelection->addTab(friends, "Friends");
    ranking = new RankWidget();
    menuSelection->addTab(ranking, "Ranking");
    setCentralWidget(menuSelection);
}

MenuWindow::~MenuWindow() {
    delete menuSelection;
    delete play;
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
}

void MenuWindow::setStart() {
    playLayout = new QVBoxLayout(play);

    playIntro = new QLabel("Choose your game's options");
    playIntro->setFont(QFont("Arial", 14, QFont::Bold));
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

    startButton = new QPushButton("START");
    connect(startButton, SIGNAL(clicked()), this, SLOT(startGame()));
    playLayout->addWidget(startButton);
}

void MenuWindow::startGame() {
    game = new GameWindow();
    game->show();
    hide();
}

