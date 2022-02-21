//
// Created by Mark Dimitrov on 15/02/2022.
//

#include <iostream>
#include "Model/Board.hpp"
#include "View/DisplayBoard.hpp"
#include "Controller/Game.h"

int main(){
    std::shared_ptr<Board> board = std::shared_ptr<Board>(new Board());

    DisplayBoard displayBoard(board);
    Game game(board, displayBoard);
    game.start();

    return 0;
}