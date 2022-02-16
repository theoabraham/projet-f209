//
// Created by Mark Dimitrov on 15/02/2022.
//
#include "Board.hpp"

int main(){
    Player player;
    Pawn pawn(0, Position{0,0}, &player);
    Board b(9);
    b.printBoard();
    return 0;
}