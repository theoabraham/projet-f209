#ifndef BOARD_HPP
#define BOARD_HPP

#include "MotherCell.hpp"
#include "Player.hpp"
#include "Position.hpp"
#include <string>
#include <array>
#include <memory>
#include <iostream>
#include <list>


class Board{
    private:
        int size;
        int boardSize;
        const int START_WALL;
        
        std::vector<std::vector< std::shared_ptr<MotherCell> > > matrix;

        std::vector<std::shared_ptr<Player>> players;
        int currentPlayer=0;
        int nplayer; 

        bool end = false;
    public:
        explicit Board(int nplayer, int size=9, int START_WALL=10);


        int getNplayer() const {return nplayer;}

        int getBoardSize() const {return boardSize;}
        std::vector<std::shared_ptr<Player>> getPlayers() const {return players;};
        std::vector<std::vector< std::shared_ptr<MotherCell> > > getMatrix() const {return matrix;}
        
        bool isEnd() const{return end;};

        /**
         * @brief s'occupe de la condition du jeu lorsque 2 pions se retrouvent face à face (voir règles)
         * @return bool: true si coup valide, false sinon 
        */ 
        bool Face2Face(Position& next_pos, int currentP);
        bool DiagonalMove(Position& next_pos, int currentP);
        bool JumpOver(Position& next_pos, int currentP);       


        /**
         * @brief Place le mur 
         * @param direction: mur horizontal ou vertical 
         *        pos: case où doit commencer le mur 
        */
        void placeWall(std::string &direction, Position &pos); 
              
        /**
         * @brief Execute le coup  
         * @param typeOfMove : type de coup (si on veut bouger le pion ou placer un mur)
         *        pos: le la case où doit aller le pion
         *        currentP: le joueur qui a entré le coup
        */
        void executeMove(std::string &typeOfMove, Position &pos, int currentP);


        /**
         * @brief vérifie si le joueur peut placer un mur là où il a joué son coup   
         * @param direction : mur horizontal ou vertical 
         *        pos : la où le mur doit être placer (pos = position cible)
         * @return bool: true si coup valide, false sinon
        */
        bool checkWall(std::string &direction, Position &pos);

        /**
         * @brief vérifie si le coup est jouable
         * @param typeOfMove : type de coup (si on veut bouger le pion ou placer un mur)
         *        move : la case qui est jouée 
         *        currentP: le joueur actuel
         * @returns bool: true si coup jouable selon les règles du jeu, false sinon
        */
        bool isValid(std::string &typeOfMove, Position &move, int currentP);

        /**
         * @brief vérifie si le coup du joueur est valide et fait appel a executeMove qui exécute le coup
         * @param input: coup entré par le joueur
         *        currentP: le joueur en question 
         * @return bool: true si coup valide, false sinon 
        */ 
        bool checkInput(std::string &input, int currentP);


        /**
         * @brief Lie les cases avec les cases de type PawnCell voisines
        */
        void bindCells();

        /**
         * @brief initialise le joueur et son pion 
         * @returns le pion initialisé  
        */
        std::shared_ptr<Pawn> setPlayer(Position pos, int id); 

        /** 
         * @brief Initialise le plateau, ses pions et ses joueurs
        */
        void newGame();

        bool possiblePaths();
};

#endif