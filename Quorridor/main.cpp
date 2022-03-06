#include <iostream>
#include "Model/Board.hpp"
#include "Model/Gamemodes/DestruQtion.hpp"
#include "View/DisplayBoard.hpp"
#include "Controller/Game.hpp"

int main(){
    int input;
    bool res = false;
    std::cout<<"Combien de joueurs êtes-vous? (2 ou 4)"<<std::endl;
    while (not res){
        std::cin>>input;
        if (input==2 || input==4) res= true;  
    }
        
    std::shared_ptr<Board> board = std::shared_ptr<Board>(new DestruQtionBoard(input));
    auto displayBoard = std::shared_ptr<DisplayBoard>(new DisplayBoard(board));
    
    Game game(board, displayBoard);
    game.start();

    return 0;
}