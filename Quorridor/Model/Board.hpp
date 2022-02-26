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
        std::vector<std::shared_ptr<Player>> getPlayers() const {return players;};
        std::vector<std::vector< std::shared_ptr<MotherCell> > > getMatrix() const {return matrix;}

        void placeWall(std::string &direction, Position &pos); 
              
        /**
         * @brief Execute le coup  
         * @param pos: le la case où doit aller le pion
         * 
        */
        void executeMove(std::string &typeOfMove, Position &pos, int currentP);

        bool checkWall(Position &playerPos, Position next_cell);

        /**
         * @brief vérifie si le coup est jouable
        */
        bool isValid(std::string &typeOfMove, Position &move, Position &playerPos);


        /**
         * @brief vérifie si le coup du joueur est valide 
         * @param input: coup entré par le joueur
         *        currentP: le joueur en question 
         * @return bool: true si coup valide false sinon 
        */ 
        bool checkInput(std::string &input, int currentP);

        /**
         * @brief Lie les cases avec les cases de type PawnCell voisines
        */
        void bindCells();


        /** 
         * @brief Initialise le plateau, ses pions et ses joueurs
        */
        void newGame();        
};

#endif