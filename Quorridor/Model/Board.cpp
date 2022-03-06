#include "Board.hpp"

Board::Board(int nplayer, int size, const int START_WALL): START_WALL{START_WALL}, nplayer{nplayer}, size{size} {
    newGame();
}


std::vector<int> Board::sidesP(Position& target_pos, int currentP){
    Position player_pos = players[currentP]->getPawnPos();
        Position difference = player_pos - target_pos;
        difference.setX(-difference.getX());
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
    return sides; 
}


bool Board::DiagonalMove(Position &target_pos, int currentP) {
    Position player_pos = players[currentP]->getPawnPos();
    std::vector<int> sides = sidesP(target_pos, currentP);
    for (auto side: sides) {
        if (matrix[player_pos.getY()][player_pos.getX()]->getNeighbour(side)) {
            // Vérifie si pas de mur entre cases
            if (matrix[player_pos.getY()][player_pos.getX()]->getNeighbour(side)->occupied()) {
                switch (side) {
                    case 0:
                        if (matrix[player_pos.getY() - 3][player_pos.getX()]->occupied() and
                            not matrix[target_pos.getY()][target_pos.getX()]->occupied()) {
                            return true; //Mur derrière pion voisin et case cible pas occupée
                        }
                    case 2:

                        if (matrix[player_pos.getY() + 3][player_pos.getX()]->occupied() and
                            not matrix[target_pos.getY()][target_pos.getX()]->occupied()) {
                            return true;
                        }
                    case 1:
                        if (matrix[player_pos.getY()][player_pos.getX() + 3]->occupied() and
                            not matrix[target_pos.getY()][target_pos.getX()]->occupied()) {
                            return true; //Mur derrière pion voisin et case cible pas occupée
                        }
                    case 3:
                        if (matrix[player_pos.getY()][player_pos.getX() - 3]->occupied() and
                            not matrix[target_pos.getY()][target_pos.getX()]->occupied()) {

                            return true; //Mur derrière pion voisin et case cible pas occupée
                        }
                }
            }
        }
    }
    return false;
}

bool Board::JumpOver(Position &target_pos, int currentP) {
    Position player_pos = players[currentP]->getPawnPos();

    Position diff = (player_pos - target_pos) / 4;


    if (matrix[player_pos.getY() - diff.getY() * 2][player_pos.getX() - diff.getX() * 2]->occupied()) {
        //Si la case voisine est bien occupée
        if (not matrix[player_pos.getY() - diff.getY() * 3][player_pos.getX() - diff.getX() * 3]->occupied()) {
            //Si il n'y a pas de murs entre les pions
            if (not matrix[player_pos.getY() - diff.getY() * 4][player_pos.getX() - diff.getX() * 4]->occupied())
                //Si la case voisine suivante est libre
                return true;
        }
    }
    return false;
}


bool Board::Face2Face(Position &target_pos, int currentP) {
    Position player_pos = players[currentP]->getPawnPos();
    Position difference = player_pos - target_pos;
       
    switch (difference.getX()) {
        case 4:
            if (difference.getY() == 0) {
                return JumpOver(target_pos, currentP);
            }
        case -4:
            if (difference.getY() == 0) {
                return JumpOver(target_pos, currentP);

            }
        case 0:
            switch (difference.getY()) {
                case 4:
                    return JumpOver(target_pos, currentP);
                case -4:

                    return JumpOver(target_pos, currentP);
            }
        case 2:
            if (difference.getY() == 2 or difference.getY() == -2) {
                return DiagonalMove(target_pos, currentP);
            }
        case -2:
            if (difference.getY() == 2 or difference.getY() == -2) {
                return DiagonalMove(target_pos, currentP);

            }
    }
    return false;
}


void Board::placeWall(std::string &direction, Position &pos) {
    int posX, posY;
    if (direction == "H") { // Placement d'un mur horizontal
        for (int i = 0; i < 3; i++) { // Décalage sur les case de Murs
            posY = pos.getY() - 1;
            posX = pos.getX() + i;
            std::shared_ptr<Wall> wall = std::shared_ptr<Wall>(new Wall(Position{posX, posY}, direction)); 
            matrix[posY][posX]->setPiece(wall);            
            updateNeighbours(wall, Position{posX, posY}, direction);

        }
    } else if (direction == "V") { // Placement d'un mur vertical
        for (int i = 0; i < 3; i++) { // Décalage sur les case de Murs
            posY = pos.getY() - i;
            posX = pos.getX() + 1;
            std::shared_ptr<Wall> wall = std::shared_ptr<Wall>(new Wall(Position{posX, posY}, direction)); 
            matrix[posY][posX]->setPiece(wall);            
            updateNeighbours(wall, Position{posX, posY}, direction);
        }
    }
    players[currentPlayer]->useWall();
}


void Board::executeMove(std::string &typeOfMove, Position &pos, int currentP) {
    if (typeOfMove == "P") {
        Position playerPos = players[currentP]->getPawnPos();
        players[currentP]->setPawnPos(pos);

        matrix[pos.getY()][pos.getX()]->setPiece(players[currentP]->getPawn()); // Bouger le Pion sur la prochaine case
        matrix[playerPos.getY()][playerPos.getX()]->setPiece(nullptr); // le supprimer de la case précédente

        // On vérifie si un des joueurs a gagné:
        switch (currentP) {
            case 0:
                if (players[currentP]->getPawnPos().getY() == boardSize - 1) end = true;
                break;
            case 1:
                if (players[currentP]->getPawnPos().getY() == 0) end = true;
                break;
            case 2:
                if (players[currentP]->getPawnPos().getX() == 0) end = true;
                break;
            case 3:
                if (players[currentP]->getPawnPos().getX() == boardSize - 1) end = true;
                break;
        }
    } else {
        placeWall(typeOfMove, pos);
    }
}


bool Board::checkWall(std::string &direction, Position &target_pos) {
    int posX, posY;
    if (direction == "H") {
        if (target_pos.getX()<boardSize-2 && target_pos.getY()>0){ 

            for (int i = 0; i < 3; i++) {
                posY = target_pos.getY() - 1; // décalage vers les WallCell
                posX = target_pos.getX() + i; // longueur du mur
                if (matrix[posY][posX]->occupied()) return false;
            }

        } else return false;
    } else {
        if (target_pos.getX()<boardSize-2 && target_pos.getY()>0){ 
            for (int i = 0; i < 3; i++) {
                posY = target_pos.getY() - i; // décalage vers les WallCell
                posX = target_pos.getX() + 1; // longueur du mur
                if (matrix[posY][posX]->occupied()) return false;

            }
        } else return false;
    }
    return true;
}


bool Board::isValid(std::string &typeOfMove, Position &next_pos, int currentP) {
    bool res = false;

    Position playerPos = players[currentP]->getPawnPos();
    if (typeOfMove == "P") { // mouvement de Pion

        Position next_cell = (playerPos - next_pos) / 2;
        next_cell.setX(-next_cell.getX()); 

        if (matrix[playerPos.getY()][playerPos.getX()]->getNeighbour(next_cell)) {
            //Si la prochaine case est une case voisine et Si il n'y a pas de mur bloquant le déplacement
            if (not matrix[playerPos.getY()][playerPos.getX()]->getNeighbour(next_cell)->occupied()) {
                //Si la prochaine case voisine est libre
                    res = true;
            }
        } else
            return Face2Face(next_pos, currentP); // on vérifie si le joueur souhaite sauter au dessus du joueur adverse

    } else if (typeOfMove == "H" || typeOfMove == "V") { // placer un mur

        if (players[currentP]->hasWalls()) {
            res = checkWall(typeOfMove, next_pos);
        }
    }

    return res;
}


bool Board::checkInput(std::string &input, int currentP) {
    int len;
    if (size >= 10) { // on verifie la taille du message en fonction de la taille du plateau
        if (input.size() != 5) return false;
        len = 4;
    } else {
        if (input.size() != 4) return false;
        len = 3;
    }

    std::string typeOfMove{input.substr(0, 1)};

    Position target_pos{input.substr(2, len)};

    target_pos = target_pos * 2; //*2 pour avoir la vrai position sur la matrice

    currentPlayer = currentP;
    if (isValid(typeOfMove, target_pos, currentP)) {
        executeMove(typeOfMove, target_pos, currentP);
        if(typeOfMove=="H" or typeOfMove=="V"){
            //if(!possiblePaths()){
                //removeWall(typeOfMove, target_pos);
        players[currentPlayer]->addWall();
            //return false;
            //}
        }
        return true;
    }
    return false;
}

void Board::updateNeighbours(std::shared_ptr<Piece> piece, Position pos, std::string direction){

    if (piece == nullptr){
        std::shared_ptr<MotherCell> neighbour = matrix[pos.getY()][pos.getX()]; 
        if (direction=="H"){
            matrix[pos.getY() + 1][pos.getX()]->setNeighbour(neighbour, 0); 
            matrix[pos.getY() - 1][pos.getX()]->setNeighbour(neighbour, 2); 
        }
        else {
            matrix[pos.getY()][pos.getX() - 1]->setNeighbour(neighbour, 1);             
            matrix[pos.getY()][pos.getX() + 1]->setNeighbour(neighbour, 3); 
        }
    }
    else {
        //On met a jour les voisins puisque du coté où est posé le mur le pion ne peut plus bouger --> nullptr
        if (piece->wallD()=="H"){
            matrix[pos.getY() + 1][pos.getX()]->setNeighbour(nullptr, 0); 
            matrix[pos.getY() - 1][pos.getX()]->setNeighbour(nullptr, 2); 
        }      
        else {
            matrix[pos.getY()][pos.getX() - 1]->setNeighbour(nullptr, 1);             
            matrix[pos.getY()][pos.getX() + 1]->setNeighbour(nullptr, 3);             
        }
    }
}

void Board::bindCells() {
    for (int i = 0; i < boardSize; i += 2) {
        for (int j = 0; j < boardSize; j += 2) {
            std::vector<std::shared_ptr<MotherCell>> neighbours{nullptr, nullptr, nullptr, nullptr};
            if (i > 0) {
                //Lie case haut
                neighbours[0] = matrix[i - 2][j];
            }
            if (j < boardSize - 2 ) { 
                //Lie case droite
                neighbours [1] = matrix[i][j + 2]; 
            }
            if (i < boardSize - 2) {
                //Lie case bas
                neighbours[2] = matrix[i + 2][j];
            }
            if (j > 0) {
                //Lie case gauche
                neighbours[3] = matrix[i][j - 2]; 
            }
            matrix[i][j]->setNeighbours(neighbours);
        }
    }
}

std::shared_ptr<Pawn> Board::setPlayer(Position pos, int id) {
    std::shared_ptr<Pawn> pawn = std::shared_ptr<Pawn>(new Pawn(pos, id));

    std::shared_ptr<Player> player = std::shared_ptr<Player>(new Player(id, pawn, START_WALL));
    players.push_back(player);
    return pawn;
}

void Board::newGame() {
    boardSize = size * 2 - 1;
    for (int i = 0; i < boardSize; i++) {
        std::vector<std::shared_ptr<MotherCell> > line;
        for (int j = 0; j < boardSize; j++) {

            //Initialisation des cases: 

            if ((i % 2 != 0 and i < boardSize) or (j % 2 != 0 and j < boardSize)) {
                line.push_back(std::shared_ptr<MotherCell>(new MotherCell()));
            } else {
                line.push_back(std::shared_ptr<MotherCell>(new MotherCell()));

            }

            //Initialisation des pions et joueurs: 
            if (i == 0 and j == boardSize/2) {
                line[j]->setPiece(setPlayer(Position{j,i}, players.size()));              
            }
            if (i == boardSize-1 and j == boardSize/2) {
                line[j]->setPiece(setPlayer(Position{j,i}, players.size()));
            }

            if (nplayer==4){
                if (i == boardSize/2 and j == 0) {
                line[j]->setPiece(setPlayer(Position{j,i}, players.size()));              
                }
                if (i == boardSize/2 and j == boardSize-1) {
                    line[j]->setPiece(setPlayer(Position{j,i}, players.size()));
                } 
            }

        }
        matrix.push_back(line);
    }
    bindCells();
}

bool Board::possiblePaths() {
    int nb_players = players.size();
    bool endOfSearch;
    int player_id = 0;
    for (const auto &player: players) {
        endOfSearch = false;
        std::cout<<player->getId()<<std::endl;
        std::vector<std::vector<bool>> visited(size, std::vector<bool>(size, false));
        std::list<Position> queue;
        Position pawn = player->getPawnPos();
        visited[pawn.getY() / 2][pawn.getX() / 2] = true;
        queue.push_back(pawn);
        while (!queue.empty() and not endOfSearch) {
            Position s = queue.front();
            std::cout << "(" << s.getX()/2 << ", " << s.getY()/2<<")" << std::endl;
            queue.pop_front();
            for (int i = 0; i < 4; i++) {
                if (matrix[s.getY()][s.getX()]->getNeighbour(i)) {
                    Position difference(0, 0);
                    switch (i) {
                        case 0:
                            difference.setY(-2);
                            break;
                        case 1:
                            difference.setX(2);
                            break;
                        case 2:
                            difference.setY(+2);
                            break;
                        case 3:
                            difference.setX(-2);
                            break;
                    }
                    if (!visited[(s.getY() + difference.getY())/2][(s.getX() + difference.getX())/2]) {
                        std::cout << "okkkkk"<<std::endl;
                        visited[(s.getY() + difference.getY())/2][(s.getX() + difference.getX())/2] = true;
                        queue.emplace_back(s.getY() + difference.getY(), s.getX() + difference.getX());
                        switch (nb_players) {
                            case 2:
                                switch (player_id) {
                                    case 0:
                                        std::cout<<"case 0"<<std::endl;
                                        std::cout<< (s.getY())<<" "<< difference.getY() << "  " << boardSize-1<<std::endl;
                                        if ((s.getY() + difference.getY()) == boardSize-1) {
                                            std::cout<<"ok"<<std::endl;
                                            endOfSearch = true;
                                        }
                                        break;
                                    case 1:
                                        if (s.getY() + difference.getY() == 0) {
                                            endOfSearch = true;
                                        }
                                        break;
                                }
                                break;
                            case 4:
                                switch (player_id) {
                                    case 0:
                                        if (s.getY() + difference.getY() == boardSize-1) {
                                            endOfSearch = true;
                                        }
                                        break;
                                    case 1:
                                        if (s.getX() + difference.getX() == 0) {
                                            endOfSearch = true;
                                        }
                                        break;
                                    case 2:
                                        if (s.getY() + difference.getY() == 0) {
                                            endOfSearch = true;
                                        }
                                        break;
                                    case 3:
                                        if (s.getX() + difference.getX() == boardSize - 1) {
                                            endOfSearch = true;
                                        }
                                        break;
                                }
                                break;

                        }
                    }
                }
            }
        }
        if(not endOfSearch)
            return endOfSearch;
        player_id++;
    }
    return endOfSearch;
}

void Board::removeWall(const std::string &direction, Position &pos) {
    int posX, posY;
    if (direction == "H") {
        for (int i = 0; i < 3; i++) {
            posY = pos.getY() - 1;
            posX = pos.getX() + i;
            matrix[posY][posX]->setPiece(nullptr);
            updateNeighbours(nullptr, Position{posX, posY}, direction);

        }
    } else if (direction == "V") {
        for (int i = 0; i < 3; i++) {
            posY = pos.getY() - i;
            posX = pos.getX() + 1;
            updateNeighbours(nullptr, Position{posX, posY}, direction);
            matrix[posY][posX]->setPiece(nullptr);
        }
    }
}
