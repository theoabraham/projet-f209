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
        std::shared_ptr<MotherCell> getNeighbour(int neighbourPos);
        void blockNeighbour(int neighbourPos);
        void setNeighbours(std::vector<std::shared_ptr<MotherCell>> &neighbours);
        bool occupied();
        virtual void set(std::shared_ptr<Piece> piece);
        virtual std::shared_ptr<Piece> getPiece();
        virtual void delPiece();
        bool isNeighbour(Position neighbourPos);
};


class PawnCell : public MotherCell{
public:
    std::shared_ptr<Piece> getPiece() override;
    void set(std::shared_ptr<Piece> piece) override;
};



class WallCell: public MotherCell{
public:
    std::shared_ptr<Piece> getPiece() override;
    void set(std::shared_ptr<Piece> piece) override;
};


#endif