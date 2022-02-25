#ifndef MOTHERCELL_HPP
#define MOTHERCELL_HPP

#include <memory>
#include <vector>
#include "Piece.hpp"


class MotherCell{
protected:
    std::shared_ptr<Piece> cellPiece;
    std::vector<std::shared_ptr<MotherCell>> pawnsNeighbours{nullptr, nullptr, nullptr, nullptr};
    std::vector<std::shared_ptr<MotherCell>> wallsNeighbours{nullptr, nullptr, nullptr, nullptr};
public:
        virtual std::shared_ptr<Piece> getPiece() {return cellPiece;}
        virtual void setPiece(std::shared_ptr<Piece> piece) {cellPiece = piece;}
        
        std::shared_ptr<MotherCell> getPawnsNeighbour(int neighbourPos) {return pawnsNeighbours[neighbourPos];}
        void setPawnsNeighbours(std::vector<std::shared_ptr<MotherCell>> &neighboursVector) {pawnsNeighbours = neighboursVector;}          
        bool isPawnsNeighbour(Position neighbourPos);   
        
        
        std::shared_ptr<MotherCell> getWallsNeighbour(Position neighbourPos); 
        void setWallsNeighbours(std::vector<std::shared_ptr<MotherCell>> &neighboursVector) {wallsNeighbours = neighboursVector;}          

        bool occupied();
};
//TODO : Simplifier tout ce qui est fonction type "neighbour" +  restructurer 


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