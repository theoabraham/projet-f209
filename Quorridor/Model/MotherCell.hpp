#ifndef MOTHERCELL_HPP
#define MOTHERCELL_HPP

#include <memory>
#include <vector>
#include "Piece.hpp"


class MotherCell{
protected:
    std::shared_ptr<Piece> cellPiece;
    std::vector<std::shared_ptr<MotherCell>> neighbours{nullptr, nullptr, nullptr, nullptr};
public:
        virtual std::shared_ptr<Piece> getPiece() {return cellPiece;} //En faire des fonctions abstraites ? ("=0;")
        virtual void setPiece(std::shared_ptr<Piece> piece) {cellPiece = piece;}
        bool occupied();

        void setNeighbours(std::vector<std::shared_ptr<MotherCell>> &neighboursVector) {neighbours = neighboursVector;}          

        /**
         *@brief s'occupe d'obtenir le case voisine   
         *@param neighbourPos: la case voisine selon l'indice de la case de initiale
         *                     (ex: pour la case du bas: Position(0, -1))
         *@returns la case voisine en question 
        */
        std::shared_ptr<MotherCell> getNeighbour(Position &neighbourPos); 
        
        
};

class PawnCell : public MotherCell{
public:
    std::shared_ptr<Piece> getPiece() override;
    void setPiece(std::shared_ptr<Piece> piece) override;
};

class WallCell: public MotherCell{
public:
    std::shared_ptr<Piece> getPiece() override;
    void setPiece(std::shared_ptr<Piece> piece) override;
};

#endif