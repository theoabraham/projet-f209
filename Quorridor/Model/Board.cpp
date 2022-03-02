#include "Board.hpp"

Board::Board(int nplayer, int size) : size{size}, nplayer{nplayer} {
    newGame();
}

bool Board::DiagonalMove(Position &next_pos, int currentP) {
    Position player_pos = players[currentP]->getPawnPos();
    Position difference = player_pos - next_pos;
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
    for (auto side: sides) {

        if (matrix[player_pos.getY()][player_pos.getX()]->getNeighbour(side)) {// Vérifie si pas de mur entre cases
            if (matrix[player_pos.getY()][player_pos.getX()]->getNeighbour(side)->occupied()) {

        if (matrix[player_pos.getY()][player_pos.getX()]->getNeighbour(side)) {
            // Vérifie si pas de mur entre cases
            if (matrix[player_pos.getY()][player_pos.getX()]->getNeighbour(side)->occupied()) {
                // Pion sur case voisine

                switch (side) {
                    case 0:
                        if (matrix[player_pos.getY() - 3][player_pos.getX()]->occupied() and
                            not matrix[next_pos.getY()][next_pos.getX()]->occupied()) {
                            return true; //Mur derrière pion voisin et case cible pas occupée
                        }
                    case 2:
                        if (matrix[player_pos.getY()+3][player_pos.getX()]->occupied() and
                            not matrix[next_pos.getY()][next_pos.getX()]->occupied()) {
                            return true;
                        }
                    case 1:
                        if (matrix[player_pos.getY()][player_pos.getX()+3]->occupied() and
                            not matrix[next_pos.getY()][next_pos.getX()]->occupied()) {
                            return true; //Mur derrière pion voisin et case cible pas occupée
                        }
                    case 3:
                        if (matrix[player_pos.getY()][player_pos.getX()-3]->occupied() and
                            not matrix[next_pos.getY()][next_pos.getX()]->occupied()) {
                            return true; //Mur derrière pion voisin et case cible pas occupée
                        }
                }
            }
        }
    }
    return false;
}

bool Board::JumpOver(Position &next_pos, int currentP) {
    Position player_pos = players[currentP]->getPawnPos();
    Position diff = (player_pos - next_pos)/4;

    if (matrix[player_pos.getY()-diff.getY()*2][player_pos.getX() - diff.getX()*2]->occupied()){
        //Si la case voisine est bien occupée
        if (not matrix[player_pos.getY() - diff.getY()*3][player_pos.getX() - diff.getX()*3]->occupied()){
            //Si il n'y a pas de murs entre
            if (not matrix[player_pos.getY() - diff.getY()*4][player_pos.getX() - diff.getX()*4]->occupied())
                //Si la case voisine suivante est libre
                return true; 
        }
    }
    return false;
}                


bool Board::Face2Face(Position &next_pos, int currentP) {
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

        //On vérifie si un des joueur a gagné: 
        switch (currentP) {
            case 0:
                if (players[currentP]->getPawnPos().getY() == boardSize-1) end = true;
                break;
            case 1:
                if (players[currentP]->getPawnPos().getY() == 0) end = true;
                break;    
            case 2:
                if (players[currentP]->getPawnPos().getX() == 0) end = true;
                break;
            case 3:
                if (players[currentP]->getPawnPos().getX() == boardSize-1) end = true;
                break;            
        }
    } else {
        placeWall(typeOfMove, pos);
    }
}

bool Board::checkWall(std::string &direction, Position &next_pos){
    int posX, posY;
    if (direction == "H") {
        Position wallPos{next_pos.getX(), next_pos.getY() - 1}; // Case cible (voir srd)
        if (wallPos.getY() > 0 && (wallPos.getX() + 2 < boardSize)){
            for (int i = 0; i < 3; i++) {
                posY = next_pos.getY() - 1;
                posX = next_pos.getX() + i;
                if (matrix[posY][posX]->occupied()) return false;
            }
        } 
        else return false;    
    }
    else { 
        Position wallPos{next_pos.getX() + 1, next_pos.getY()}; // Case cible (voir srd)
        std::cout<<wallPos.getX()<<" "<< wallPos.getY()<<std::endl; 
        if (wallPos.getY() > 0 && (wallPos.getX() + 2 < boardSize)){ 
            for (int i = 0; i < 3; i++) {
            posY = next_pos.getY() - i;
            posX = next_pos.getX() + 1;
            if (matrix[posY][posX]->occupied()) return false; 
            }
        }
        else return  false; 
    }
    return true;
}    
    

bool Board::isValid(std::string &typeOfMove, Position &next_pos, int currentP) {
    bool res = false; 
    Position playerPos = players[currentP]->getPawnPos();
    if (typeOfMove == "P") {
        Position next_cell = (playerPos - next_pos)/2;  
        if (matrix[playerPos.getY()][playerPos.getX()]->getNeighbour(next_cell)) {
            //Si la prochaine case est une case voisine 
            if (not matrix[playerPos.getY()][playerPos.getX()]->getNeighbour(next_cell)->occupied()) {
                //Si la prochaine case voisine est libre
                if (not matrix[playerPos.getY() - next_cell.getY()][playerPos.getX() + next_cell.getX()]->occupied())
                    //Si il n'y a pas de mur entre
                    res = true;
            }
        }else
            return Face2Face(next_pos,currentP);    
    
    } else if (typeOfMove == "H" || typeOfMove == "V") {
        
        if (players[currentP]->hasWalls()) {
            res = checkWall(typeOfMove,next_pos); 
        }
    }
    
    return res;
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
        executeMove(typeOfMove, next_pos, currentP);
        return true;
    }
    return false;
}

void Board::bindCells() {
    for (int i = 0; i < boardSize; i += 2) {
        for (int j = 0; j < boardSize; j += 2) {
            std::vector<std::shared_ptr<MotherCell>> neighbours;
            if (i > 0) {
                neighbours.push_back(matrix[i - 2][j]);
            } else {
                neighbours.push_back(nullptr);
            }
            if (j < boardSize -3) {
                neighbours.push_back(matrix[i][j + 2]);
            } else {
                neighbours.push_back(nullptr);
            }
            if (i < boardSize -3) {
                neighbours.push_back(matrix[i + 2][j]);
            } else {
                neighbours.push_back(nullptr);
            }
            if (j > 0) {
                neighbours.push_back(matrix[i][j - 2]);
            } else {
                neighbours.push_back(nullptr);
            }
            matrix[i][j]->setNeighbours(neighbours);
        }
    }
}

std::shared_ptr<Pawn> Board::setPlayer(Position pos, int id){
    std::shared_ptr<Pawn> pawn = std::shared_ptr<Pawn>(new Pawn(pos, id));

    std::shared_ptr<Player> player = std::shared_ptr<Player>(new Player(id, pawn));
    players.push_back(player);
    return pawn; 
} 

void Board::newGame() {
    boardSize = size * 2 - 1;
    for (int i = 0; i < size * 2 - 1; i++) {
        std::vector<std::shared_ptr<MotherCell> > line;
        for (int j = 0; j < size * 2 - 1; j++) {

            //Initialisation des cases: 
            if ((i % 2 != 0 and i < boardSize) or (j % 2 != 0 and j < boardSize)) { 
                line.push_back(std::shared_ptr<WallCell>(new WallCell()));
            } else { 
                line.push_back(std::shared_ptr<PawnCell>(new PawnCell()));
            }

            //Initialisation des pions et joueurs: 
            if (i == 10 and j == 8) {
                line[j]->setPiece(setPlayer(Position{j,i}, 0));              
            }
            if (i == 16 and j == 8) {
                line[j]->setPiece(setPlayer(Position{j,i}, 1));
            }

            if (nplayer==4){
                if (i == 8 and j == 0) {
                line[j]->setPiece(setPlayer(Position{j,i}, 2));              
                }
                if (i == 8 and j == 16) {
                    line[j]->setPiece(setPlayer(Position{j,i}, 3));
                } 
            }

        }
        matrix.push_back(line);
    }
    bindCells();

}

bool Board::possiblePaths() {
    for(const auto& player:players){
    std::vector<std::vector<bool>> visited(size,std::vector<bool>(size, false));
    std::list<std::shared_ptr<MotherCell>>queue;
    bool end = false;
    Position pawn = player->getPawnPos();
    visited[pawn.getY()/2][pawn.getX()/2] = true;
    queue.push_back(matrix[pawn.getY()][pawn.getX()]);
    while(!queue.empty() and not end){
        std::shared_ptr<MotherCell> s = queue.front();
        queue.pop_front();
        for(int i = 0; i<4;i++){
            if(s->getNeighbour(i) ){
                Position difference(0,0);
                switch (i) {
                    case 0:
                        difference.setY(-1);
                        break;
                    case 1:
                        difference.setX(1);
                        break;
                    case 2:
                        difference.setY(+1);
                        break;
                    case 3:
                        difference.setX(-1);
                        break;
                }
                if(!visited[pawn.getY()+difference.getY()][pawn.getX()+difference.getX()]){
                    visited[pawn.getY()+difference.getY()][pawn.getX()+difference.getX()]=true;
                    queue.push_back(s->getNeighbour(i));
                }
            }
        }
    }
    }

    return false;
}









}

