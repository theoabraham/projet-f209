#include "DestruQtion.hpp"

bool DestruQtionBoard::checkWall(std::string &direction, Position &target_pos){
    //si l'emplacement du mur horizontal est occupé, on détruit le mur ciblé
    if (direction == "H" && matrix[target_pos.getY() - 1][target_pos.getX()]->occupied()) {
        return true;
    }
    //Pareil à la verticale
    if (direction == "V" && matrix[target_pos.getY()][target_pos.getX() + 1]->occupied()) {
        return true;
    }
    return Board::checkWall(direction, target_pos);
}

void DestruQtionBoard::placeWall(std::string &direction, Position &pos) {
    int posX = pos.getX(), posY = pos.getY();
    //Destruction de mur
    if (direction == "H" && matrix[pos.getY() - 1][pos.getX()]->occupied()) {
        destroyWall(matrix[pos.getY() - 1][pos.getX()]->getPiece());
    }
    else if (direction == "V" && matrix[pos.getY()][pos.getX() + 1]->occupied()) {
        destroyWall(matrix[pos.getY()][pos.getX() + 1]->getPiece());
    }
    // Placement de mur
    else {
        std::vector<std::shared_ptr<DestruQtionWall>> triplets;
        if (direction == "H") { // Mur horizontal
            for (int i = 0; i < 3; i++) {
                posY = pos.getY() - 1;
                posX = pos.getX() + i;
                triplets.push_back(std::shared_ptr<DestruQtionWall>(new DestruQtionWall(Position{posX, posY}, direction)));
                matrix[posY][posX]->setPiece(triplets[i]);
            }
        } else if (direction == "V") { // Mur vertical
            for (int i = 0; i < 3; i++) {
                posY = pos.getY() - i;
                posX = pos.getX() + 1;
                triplets.push_back(std::shared_ptr<DestruQtionWall>(new DestruQtionWall(Position{posX, posY}, direction)));
                matrix[posY][posX]->setPiece(triplets[i]);
            }
        }
        for (int i = 0; i < 3; i++) {
            triplets[i]->setTriplet(triplets[(i+1) % 3]);
            triplets[i]->setTriplet(triplets[(i+2) % 3]);
        }
    }
    players[currentPlayer]->useWall();
}

void DestruQtionBoard::destroyWall(std::shared_ptr<Piece> wall) {
    int posY, posX;
    for (auto w: wall->getTriplet()) { // On détruit les triplets de wall
        posY = w->getPos().getY();
        posX = w->getPos().getX();
        matrix[posY][posX]->setPiece(nullptr);
    }
    posY = wall->getPos().getY();
    posX = wall->getPos().getX();
    matrix[posY][posX]->setPiece(nullptr); // Comme les murs sont réferencé par shared_ptr, a la fin de cette fonction il n'existera plus de ptr vers l'objet ce qui l'efface
}