#include "Game.hpp"

#include <utility>

Game::Game(std::shared_ptr<Board> model, DisplayBoard &view):model{std::move(model)},view{&view} {
}

std::string Game::getInput() {
    std::string input;
    std::cin >> input;
    return input;
}


void Game::start() {
    int player = 0;
    view->printBoard();
    while(true){
        std::cout<<" Player " + std::to_string(player+1) + "'s move: (e1 = next position)"<<std::endl;
        std::string input = model->getPlayers()[player]->getInput();
        if(model->checkInput(input, player)){
            //Si le coup valide -> joueur suivant 
            player=(player+1)%2;
        }
        view->printBoard();
    }
}
