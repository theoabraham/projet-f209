#ifndef MOTHERCELL_HPP
#define MOTHERCELL_HPP

#include <memory>
#include <vector>
#include "Piece.hpp"



class MotherCell{
protected:
    std::shared_ptr<Piece> cellPiece;
    std::vector<MotherCell*> neighbours{nullptr, nullptr, nullptr, nullptr};
public:
        MotherCell* getNeighbour(int neighbourPos);
        void blockNeighbour(int neighbourPos);
        void setNeighbours(std::vector<MotherCell*> &neighbours);
        bool occupied();
        virtual void set(std::shared_ptr<Piece> piece);
        virtual std::shared_ptr<Piece> getPiece();
        virtual void delPiece();
};


class PawnCell : public MotherCell{
public:
    //bool occupied() override;
    std::shared_ptr<Piece> getPiece() override;
    void set(std::shared_ptr<Piece> piece) override;
};



class WallCell: public MotherCell{
public:
    //bool occupied() override;
    std::shared_ptr<Piece> getPiece() override;
    void set(std::shared_ptr<Piece> piece) override;
};


#endif