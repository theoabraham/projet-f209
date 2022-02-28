#include "Board.hpp"

Board::Board(int size) : size{size} {
    newGame();
}


void Board::placeWall(std::string &direction, Position &pos) {
    int posX, posY;
    if (direction == "H") {
        for (int i = 0; i < 3; i++) {
            posY = pos.getY() - 1;
            posX = pos.getX() + i;
            matrix[posY][posX]->setPiece(std::shared_ptr<Wall>(new Wall(Position{posX, posY}, direction)));
        }
    } else if (direction == "V") {
        for (int i = 0; i < 3; i++) {
            posY = pos.getY() - i;
            posX = pos.getX() + 1;
            matrix[posY][posX]->setPiece(std::shared_ptr<Wall>(new Wall(Position{posX, posY}, direction)));
        }
    }
    players[currentPlayer]->useWall();
}

void Board::executeMove(std::string &typeOfMove, Position &pos, int currentP) {
    if (typeOfMove == "P") {
        Position playerPos = players[currentP]->getPawnPos();
        players[currentP]->setPawnPos(pos);

        matrix[pos.getY()][pos.getX()]->setPiece(players[currentP]->getPawn());
        matrix[playerPos.getY()][playerPos.getX()]->setPiece(nullptr);
        switch (currentP) {
            case 0:
                if (players[currentP]->getPawnPos().getY() == (size - 1) * 2) {
                    end = true;
                }
                break;
            case 1:
                if (players[currentP]->getPawnPos().getY() == 0) {
                    end = true;
                }
                break;
        }
    } else {
        placeWall(typeOfMove, pos);
    }
}

bool Board::isValid(std::string &typeOfMove, Position &next_pos, int currentP) {
    Position playerPos = players[currentP]->getPawnPos();
    if (typeOfMove == "P") {
        Position next_cell = Position((-(playerPos.getX() - next_pos.getX())) / 2,
                                      ((playerPos.getY()) - next_pos.getY()) / 2);

        if (matrix[playerPos.getY()][playerPos.getX()]->getNeighbour(next_cell)) {
            //Si la prochaine case est une case voisine 
            if (not matrix[playerPos.getY() - next_cell.getY() * 2][playerPos.getX() + next_cell.getX() *
                                                                                       2]->occupied()) { //if (matrix[playerPos.getY()][playerPos.getX()]->getNeighbour(next_cell)->occupied()) ne fonctionne pas, pouquoi ???
                //Si la prochaine case est libre
                if (not matrix[playerPos.getY() - next_cell.getY()][playerPos.getX() + next_cell.getX()]->occupied())
                    //Si il n'y a pas de mur entre
                    return true;
            }
        }else
            return Face2Face(next_pos,currentP);
        //TODO: condition saute mouton ("Face à face" dans règles énoncé)
    } else if (typeOfMove == "H" || typeOfMove == "V") {
        if (players[currentP]->hasWalls()) {
            if (typeOfMove == "H") {
                Position wallPos{next_pos.getX(), next_pos.getY() - 1}; // Case cible (voir srd)
                if (wallPos.getY() > 0) {
                    if (not matrix[wallPos.getY()][wallPos.getX()]->occupied()) {
                        if (wallPos.getX() + 2 < size * 2 - 1) { // case voisine libre
                            if (not matrix[wallPos.getY()][wallPos.getX() + 2]->occupied() and
                                not matrix[wallPos.getY()][wallPos.getX() +
                                                           1]->occupied()) {// case voisine et case intermédiaire libre
                                return true;
                            }
                        }
                    }
                }
            } else {
                Position wallPos{next_pos.getX() + 1, next_pos.getY()}; // Case cible (voir srd)
                if (wallPos.getX() < size * 2 - 1) {
                    if (not matrix[wallPos.getY()][wallPos.getX()]->occupied()) {
                        if (wallPos.getY() - 2 > 0) {
                            if (not matrix[wallPos.getY() - 2][wallPos.getX()]->occupied() and
                                not matrix[wallPos.getY() -
                                           1][wallPos.getX()]->occupied()) {// case voisine et case intermédiaire libre
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Board::checkInput(std::string &input, int currentP) {
    if (input.size() != 4) {
        return false;
    }
    std::string typeOfMove{input.substr(0, 1)};

    Position next_pos{input.substr(2, 3)};
    next_pos = next_pos * 2; //*2 pour avoir la vrai position sur la matrice
    currentPlayer = currentP;
    if (isValid(typeOfMove, next_pos, currentP)) {
        \
        //Si coup valide
        executeMove(typeOfMove, next_pos, currentP);
        return true;
    }
    return false;
}

void Board::bindCells() {
    // TODO Bug voisins de droite dernière ligne
    for (int i = 0; i < boardSize; i += 2) {
        for (int j = 0; j < boardSize; j += 2) {
            std::vector<std::shared_ptr<MotherCell>> neighbours;
            if (i > 0) {
                neighbours.push_back(matrix[i - 2][j]);
            } else {
                neighbours.push_back(nullptr);
            }
            if (j < boardSize - 2) {
                neighbours.push_back(matrix[i][j + 2]);
            } else {
                neighbours.push_back(nullptr);
            }
            if (i < boardSize - 2) {
                neighbours.push_back(matrix[i + 2][j]);
            } else {
                neighbours.push_back(nullptr);
            }
            if (j > 0) {
                neighbours.push_back(matrix[i][j - 2]);
            } else {
                neighbours.push_back(nullptr);
            }
            matrix[j][i]->setNeighbours(neighbours);
        }
    }
}

void Board::newGame() {
    boardSize = size * 2 - 1;
    for (int i = 0; i < size * 2 - 1; i++) {
        std::vector<std::shared_ptr<MotherCell> > line;
        for (int j = 0; j < size * 2 - 1; j++) {

            //Initialisation des cases: 
            if ((i % 2 != 0 and i < boardSize) or (j % 2 != 0 and j < boardSize)) { //Si case impaire : Mur
                line.push_back(std::shared_ptr<WallCell>(new WallCell()));
            } else { //Cases Pions
                line.push_back(std::shared_ptr<PawnCell>(new PawnCell()));
            }

            //Initialisation des pions et joueurs: 
            if (i == 10 and j == 8) {
                std::shared_ptr<Pawn> pawn1 = std::shared_ptr<Pawn>(new Pawn(Position(8, 10)));
                line[j]->setPiece(std::shared_ptr<Pawn>(pawn1));
                auto player1 = std::shared_ptr<Player>(new Player(0, pawn1));
                players.push_back(player1);
            }
            if (i == 16 and j == 8) {
                std::shared_ptr<Pawn> pawn2 = std::shared_ptr<Pawn>(new Pawn(Position(8, 16)));
                line[j]->setPiece(std::shared_ptr<Pawn>(pawn2));
                auto player2 = std::shared_ptr<Player>(new Player(1, pawn2));
                players.push_back(player2);
            }
        }
        matrix.push_back(line);
    }
    bindCells();
}

bool Board::Face2Face(Position &next_pos, int currentP) {
    std::cout<< "Face2Face "<<std::endl;
    Position player_pos = players[currentP]->getPawnPos();
    Position difference = player_pos - next_pos;
    switch (difference.getX()) {
        case 4:
            if(difference.getY() == 0){
                return JumpOver(next_pos, currentP);
            }
        case -4:
            if(difference.getY() == 0){
                return JumpOver(next_pos, currentP);
            }
        case 0:
            switch (difference.getY()) {
                case 4:
                    return JumpOver(next_pos, currentP);
                case -4:
                    return JumpOver(next_pos,currentP);
            }
        case 2:
            if(difference.getY() == 2 or difference.getY() == -2){
                return DiagonalMove(next_pos,currentP);
            }
        case -2:
            if(difference.getY() == 2 or difference.getY() == -2){
                return DiagonalMove(next_pos,currentP);
            }
    }
    return false;
}

bool Board::JumpOver(Position &next_pos, int currentP) {
    std::cout << "Jump Over"<<std::endl;
    Position player_pos = players[currentP]->getPawnPos();
    Position difference = player_pos - next_pos;
    switch (difference.getX()) {
        case 4:
            if (matrix[player_pos.getX()][player_pos.getY()]->getNeighbour(1)) {
                if (matrix[player_pos.getX()][player_pos.getY()]->getNeighbour(1)->occupied()) {
                    if (not matrix[player_pos.getX() + 3][player_pos.getY()]->occupied()) {
                        return true;
                    }
                }
            }
            break;
        case -4:
            if (matrix[player_pos.getX()][player_pos.getY()]->getNeighbour(3)) {
                if (matrix[player_pos.getX()][player_pos.getY()]->getNeighbour(3)->occupied()) {
                    if (not matrix[player_pos.getX() - 3][player_pos.getY()]->occupied()) {
                        return true;
                    }
                }
            }
            break;
        case 0:
            switch (difference.getY()) {
                case 4:
                    if (matrix[player_pos.getX()][player_pos.getY()]->getNeighbour(0)) {
                        if (matrix[player_pos.getX()][player_pos.getY()]->getNeighbour(0)->occupied()) {
                            if (not matrix[player_pos.getX()][player_pos.getY() + 3]->occupied()) {
                                return true;
                            }
                        }
                    }
                    break;
                case -4:
                    if (matrix[player_pos.getX()][player_pos.getY()]->getNeighbour(2)) {
                        if (matrix[player_pos.getX()][player_pos.getY()]->getNeighbour(2)->occupied()) {
                            if (not matrix[player_pos.getX()][player_pos.getY() - 3]->occupied()) {
                                return true;
                            }
                        }
                    }
                    break;
            }
    }
    return false;
}

bool Board::DiagonalMove(Position &next_pos, int currentP) {
    std::cout<<"Diag move"<<std::endl;
    Position player_pos = players[currentP]->getPawnPos();
    Position difference = player_pos - next_pos;
    std::vector<int> sides;
    switch (difference.getX()) {
        case 2:
            switch (difference.getY()) {
                case 2:
                    sides.push_back(0);
                    sides.push_back(1);
                    break;
                case -2:
                    sides.push_back(1);
                    sides.push_back(2);
                    break;
            }
            break;
        case -2:
            switch (difference.getY()) {
                case 2:
                    sides.push_back(3);
                    sides.push_back(0);
                    break;
                case -2:
                    sides.push_back(3);
                    sides.push_back(2);
                    break;
            }
            break;
    }
    for (auto side: sides) {
        if (matrix[player_pos.getX()][player_pos.getY()]->getNeighbour(side)) { // Vérifie si pas de mur entre cases
            if (matrix[player_pos.getX()][player_pos.getY()]->getNeighbour(side)->occupied()) { // Pion sur case voisine
                switch (side) {
                    case 0:
                        if (matrix[player_pos.getX()][player_pos.getY() + 3]->occupied() and
                            not matrix[player_pos.getX() + difference.getX()][player_pos.getY() + 2]->occupied()) {
                            return true; //Mur derrière pion voisin et case cible pas occupée
                        }
                    case 2:
                        if (matrix[player_pos.getX()][player_pos.getY() - 3]->occupied() and
                            not matrix[player_pos.getX() + difference.getX()][player_pos.getY() - 2]->occupied()) {
                            return true;
                        }
                    case 1:
                        if (matrix[player_pos.getX()+3][player_pos.getY()]->occupied() and
                            not matrix[player_pos.getX()+2][player_pos.getY() + difference.getY()]->occupied()) {
                            return true; //Mur derrière pion voisin et case cible pas occupée
                        }
                    case 3:
                        if (matrix[player_pos.getX()-3][player_pos.getY()]->occupied() and
                            not matrix[player_pos.getX()-2][player_pos.getY() + difference.getY()]->occupied()) {
                            return true; //Mur derrière pion voisin et case cible pas occupée
                        }
                }
            }
        }
    }
    return false;
}






