#pragma once

#include <vector>
#include "Piece.hpp"



class MotherCell{
protected:
    Piece* cellPiece;
    std::vector<MotherCell*> neighbours{nullptr, nullptr, nullptr, nullptr};
public:
        MotherCell* getNeighbour(int neighbourPos);
        void blockNeighbour(int neighbourPos);
        void setNeighbours(std::vector<MotherCell*> &neighbours);
        virtual bool occupied();
        virtual void set(Piece *piece);
        virtual Piece* getPiece();
        virtual void delPiece();
};


class PawnCell : public MotherCell{
public:
    bool occupied() override;
    Piece* getPiece() override;
    void set(Piece *piece) override;
};



class WallCell: public MotherCell{
public:
    bool occupied() override;
    Piece* getPiece() override;
    void set(Piece *piece) override;
};




