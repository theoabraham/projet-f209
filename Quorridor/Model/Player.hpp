//
// Created by Mark Dimitrov on 15/02/2022.
//

//Au lieu des ifndef,, utiliser "pragma once"

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <utility>
#include <vector>
#include "Piece.hpp"

class Player {
    int id;
    std::shared_ptr<Pawn> pawn; 
    std::vector<Wall> walls; 
public:    
    Player(std::shared_ptr<Pawn> pawn, int id): pawn{std::move(pawn)}, id{id} {}
    static std::string getInput();
    std::shared_ptr<Pawn> getPawn(){return pawn;};
};

#endif