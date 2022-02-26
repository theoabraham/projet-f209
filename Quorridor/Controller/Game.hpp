#include "../Model/Board.hpp"
#include "../View/DisplayBoard.hpp"
#include <string>
#include <memory>
#ifndef QUORRIDOR_GAME_H
#define QUORRIDOR_GAME_H


class Game {
private:
    std::shared_ptr<Board> model;
    std::unique_ptr<DisplayBoard> view; 
    //pour plus tard: enlever view qui sera juste géré dans main
public:
    Game(std::shared_ptr<Board> model, DisplayBoard &view);
    static std::string getInput();
    
    /**
     * @brief cout avec les explication de comment un coup doit être entré 
    */
    void inputFormat(); 
    
    void updateModel(std::string input);
    void updateView();

    /**
     * @brief Fonction qui permet aux joueur de jouer grâce à une boucle while
    */
    void start();
};


#endif //QUORRIDOR_GAME_H


