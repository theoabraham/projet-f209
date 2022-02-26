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
        virtual std::shared_ptr<Piece> getPiece() {return cellPiece;}
        virtual void setPiece(std::shared_ptr<Piece> piece) {cellPiece = piece;}
        
        std::shared_ptr<MotherCell> getNeighbour(Position &neighbourPos); 
        void setNeighbours(std::vector<std::shared_ptr<MotherCell>> &neighboursVector) {neighbours = neighboursVector;}          
        bool occupied();
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