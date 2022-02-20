//
// Created by Mark Dimitrov on 15/02/2022.
//

#include "Player.hpp"

std::string Player::getInput() {
    std::string input;
    std::cout<<" what is your input player \n"<<std::endl;
    std::cin>>input;
    return input;
}
