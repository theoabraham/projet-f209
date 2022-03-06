#ifndef MOTHERCELL_HPP
#define MOTHERCELL_HPP

#include <memory>
#include <utility>
#include <vector>
#include "Piece.hpp"

class MotherCell{
protected: 
    std::shared_ptr<Piece> cellPiece;
    std::vector<std::shared_ptr<MotherCell>> neighbours{nullptr, nullptr, nullptr, nullptr};
public:
        std::shared_ptr<Piece> getPiece() {return cellPiece;}
        void setPiece(std::shared_ptr<Piece> piece) {cellPiece = std::move(piece);}
        bool occupied();

        void setNeighbours(std::vector<std::shared_ptr<MotherCell>> &neighboursVector) {neighbours = neighboursVector;}

        /**
         *@brief s'occupe d'obtenir le case voisine   
         *@param neighbourPos: la case voisine selon l'indice de la case de initiale
         *                     (ex: pour la case du bas: Position(0, -1))
         *@returns la case voisine en question 
        */
        std::shared_ptr<MotherCell> getNeighbour(Position &neighbourPos);
        std::shared_ptr<MotherCell> getNeighbour(int side){return neighbours[side];}
        void setNeighbour(std::shared_ptr<MotherCell> neighbour, int side){neighbours[side] = neighbour;}
};

#endif