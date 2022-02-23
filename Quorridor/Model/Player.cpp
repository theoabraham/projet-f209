//
// Created by Mark Dimitrov on 15/02/2022.
//

#include "Player.hpp"

std::string Player::getInput() {
    std::string input; 
    //std::cout<<" Player's move: (ex: i0i1 (i0 = initial position/ i1 = next position)"<<std::endl;
    std::cin>>input;
    return input;
}

