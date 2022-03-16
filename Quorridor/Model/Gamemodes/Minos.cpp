#include "Minos.hpp"

void MinosGame::start() {
    int player = 0;
    int nplayer = model->getNplayer(); 
    inputFormat();
    createLabyrinth();
    while(not model->isEnd()){
        std::cout<<"Player " + std::to_string(player+1) + "'s moves : "<<std::endl;
        std::string input = getInput();
        
        if(checkInput(input, player)){
            player=(player+1)%nplayer;
            if (player == 0) {
                destroyLabyrinth();
                createLabyrinth();
            }
        }
        else inputFormat();
        view->printBoard();
    }
    std::cout << "Player "<< (player-1)%nplayer << " has won"<< std::endl;
}


void MinosGame::createLabyrinth() {
    while (wallsToPlace != 0) {
        Position position = Position((rand() % model->getBoardSize()), (rand() % model->getBoardSize())) * 2;

    }
}