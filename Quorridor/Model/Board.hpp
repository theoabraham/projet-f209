#ifndef BOARD_HPP
#define BOARD_HPP

#include "MotherCell.hpp"
#include "Player.hpp"
#include "Position.hpp"
#include <string>
#include <array>
#include <memory>

#include "iostream"


class Board{
    private:
        int size=9;
        int boardSize;
        
        std::vector<std::vector< std::shared_ptr<MotherCell> > > matrix;

        std::vector<std::shared_ptr<Player>> players;
        int currentPlayer=0;
    public:

        explicit Board(int size=9);
        int getBoardSize() const {return boardSize;}
        std::vector<std::shared_ptr<Player>> getPlayers(){return players;};
        std::vector<std::vector< std::shared_ptr<MotherCell> > > getMatrix() {return matrix;}
                
        bool checkPos(Position pos) const;

        /**
         * @brief vérifie si le coup du joueur est valide 
        */ 
        bool checkInput(std::string &input, int currentP);

        /**
         * @brief Modifie le coup selon l'input du joueur
        */
        void executeMove(Position pos1, Position pos2, int currentP);
        
        /**
         * @brief Lie les cases avec leurs cases voisines
        */
        void bindCells();
        
        /** 
         * @brief Initialise le plateau, ses pions et ses joueurs
        */
        void newGame();        
};

#endif