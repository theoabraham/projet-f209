//
// Created by Mark Dimitrov on 15/02/2022.
//

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
        std::string input = model->getPlayers()[player]->getInput();
        model->ExecuteMove(input);
        player=(player+1)%2;
        view->printBoard();
    }
}
