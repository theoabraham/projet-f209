//
// Created by Mark Dimitrov on 15/02/2022.
//
#include "Model/Board.hpp"
#include "View/DisplayBoard.hpp"
#include "string"
#include <memory>
#ifndef QUORRIDOR_GAME_H
#define QUORRIDOR_GAME_H


class Game {
private:
    std::shared_ptr<Board> model;
    std::unique_ptr<DisplayBoard> view;
public:
    Game(std::shared_ptr<Board> model, DisplayBoard &view);
    static std::string getInput();
    void updateModel(std::string input);
    void updateView();
    void start();
};


#endif //QUORRIDOR_GAME_H
