//
// Created by Mark Dimitrov on 15/02/2022.
//

#include <iostream>
#include "Model/Board.h"
#include "View/DisplayBoard.hpp"


int main(){
    std::shared_ptr<Board> board = std::shared_ptr<Board>(new Board());

    DisplayBoard displayBoard(board);
    displayBoard.printBoard(); 

    return 0;
}