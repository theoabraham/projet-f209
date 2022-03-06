#include "../Board.hpp"
#include "../Piece.hpp"

class DestruQtionWall: public Wall {
    private:
        std::vector<std::shared_ptr<Piece>> triplet; // Vecteur des autres murs apparaissant en meme temps lorsqu'on place un mur
    public:
        explicit DestruQtionWall(Position position, std::string direction): Wall(position, direction) {}
        // Setter/Getter des autres triplets du mur
        void setTriplet(std::shared_ptr<DestruQtionWall> otherWall) {triplet.push_back(otherWall);}
        std::vector<std::shared_ptr<Piece>> getTriplet() override {return triplet;}

};

class DestruQtionBoard: public Board {
        public:
    DestruQtionBoard(int nplayer, int size=9, const int START_WALL=99): Board(nplayer, size, START_WALL) {}

    /**
     * @brief Détruit un mur a la position pos ou place un mur de type DestruQtionWall
    */ 
    void placeWall(std::string &direction, Position &pos) override;

    /**
     * @brief Effectue un Board::checkWall à moins que la position exact choisi par le joueur est occupé par un mur
     * @return True si espace libre pour le mur à placer ou si exactement l'espace choisi est occupé par un mur, sinon false
    */ 
    bool checkWall(std::string &direction, Position &target_pos) override;

    /**
     * @brief Détruit le mur à la position donné dans DestruQtionBoard::placeWall
    */
    void destroyWall(std::shared_ptr<Piece> wall);

    ~DestruQtionBoard() {};

}; 