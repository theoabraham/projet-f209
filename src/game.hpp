#include "board.hpp"
#include "player.hpp"

class Game {

    Board board;
    std::vector<Player> _players;
    int _currentPlayer = -1;

    public:
        Game(std::vector<Player> players) : _players{players} {}
        bool isEnd();   //Return true si pion de _currentPlayer est arrivé au mur opposé
        void placeWall(Position pos);           //Modifie plateau en placant un mur 
        void movePawn(int id, Position newPos); //Déplace un pion du plateau vers une autre case
        void executeMove();                     //Choisit placeWall() ou movePawn()
        void nextTurn();
        void endOfGame();                       //Séquence de fin de jeu 
        void start();
};