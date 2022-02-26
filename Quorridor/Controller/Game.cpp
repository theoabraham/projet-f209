#include "Game.hpp"

#include <utility>

Game::Game(std::shared_ptr<Board> model, DisplayBoard &view):model{std::move(model)},view{&view} {
}

std::string Game::getInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void Game::inputFormat(){
    std::cout<<"Format: (ex: P e1) " <<std::endl<< "1.Type of move: P (pawn), H (horizontal Wall), V (vertical wall)" <<std::endl<< "2.move: cell number" <<std::endl;
}

void Game::start() {
    int player = 0;
    view->printBoard();
    inputFormat();
    while(true){
        std::cout<<"Player " + std::to_string(player+1) + "'s moves : "<<std::endl;
        std::string input = getInput();
        
        if(model->checkInput(input, player)){
            //Si le coup valide -> joueur suivant 
            player=(player+1)%2;
        }
        else inputFormat(); 
        view->printBoard();
    }
}
