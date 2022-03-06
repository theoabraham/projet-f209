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
        int START_WALL;
        int nplayer;
        bool end = false;

    protected:
        int boardSize;
        std::vector<std::vector< std::shared_ptr<MotherCell> > > matrix;
        std::vector<std::shared_ptr<Player>> players;
        int currentPlayer=0;
        const int size;

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
        bool Face2Face(Position& target_pos, int currentP);

        /**
         * @returns un vecteur qui indique vers quel voisin regarder 
         *          selon comment on l'utilise (pour la fonction diagonalMove) 
        */
        std::vector<int> sidesP(Position& target_pos, int currentP);

        /**
         * @brief cas de mouvement diagonal si il y a un mur derrière lors du face2face
         * @return True si le mouvement est effectué avec succès, false sinon
        */
        bool DiagonalMove(Position& target_pos, int currentP);

        /**
         * @brief cas de mouvement linéaire si il n'y a pas de mur derrière lors du face2face
         * @return True si le mouvement est effectué avec succès, false sinon
        */
        bool JumpOver(Position& target_pos, int currentP);


        /**
         * @brief Place le mur 
         * @param direction: mur horizontal ou vertical 
         *        pos: case où doit commencer le mur 
        */
        virtual void placeWall(std::string &direction, Position &pos);
              
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
        virtual bool checkWall(std::string &direction, Position &pos);

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
        virtual bool checkInput(std::string &input, int currentP);

        void updateNeighbours(std::shared_ptr<Piece> piece, Position pos, std::string direction); 

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

        /**
         * @brief Algorithme qui vérifie s'il y a encore un chemin possible pour le joueur de gagner 
         * @return true si chemin possible, false sinon  
        */
        bool possiblePaths();

        virtual void destroyWall(const std::string& direction, Position& pos);

        virtual ~Board() {}
};

#endif