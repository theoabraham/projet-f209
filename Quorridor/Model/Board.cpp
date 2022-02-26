#include "Board.hpp"

Board::Board(int size): size{size} {
    newGame(); 
}


void Board::placeWall(std::string &direction, Position &pos){
    int posX, posY; 
    if (direction=="H"){
        for (int i=0; i<3; i++){
            posY = pos.getY()-1; posX = pos.getX()+i; 
            matrix[posY][posX]->setPiece(std::shared_ptr<Wall>(new Wall(Position{posX, posY}, direction)));
            //TODO: décrementer le nombre de murs que peut encore placer le joueur 
        }
    }
    else if (direction == "V"){
        for (int i=0; i<3; i++){
            posY = pos.getY()-i; posX = pos.getX()+1; 
            matrix[posY][posX]->setPiece(std::shared_ptr<Wall>(new Wall(Position{posX, posY}, direction)));  
            //TODO: décrementer le nombre de murs que peut encore placer le joueur 
        }
    }
}

void Board::executeMove(std::string &typeOfMove, Position &pos, int currentP ) { 
    if (typeOfMove=="P"){
        Position playerPos = players[currentP]->getPawnPos();
        players[currentP]->setPawnPos(pos);
        
        matrix[pos.getY()][pos.getX()]->setPiece(players[currentP]->getPawn()); 
        matrix[playerPos.getY()][playerPos.getX()]->setPiece(nullptr); 
        
    }
    else{
        placeWall(typeOfMove,pos); 
    }
}

bool Board::isValid(std::string &typeOfMove, Position &next_pos, Position &playerPos){
    if (typeOfMove=="P"){
       Position next_cell = Position((-(playerPos.getX()-next_pos.getX()))/2,((playerPos.getY())-next_pos.getY())/2); 

        std::cout<<"Next cell: "<<next_cell.getX()<<" "<<next_cell.getY()<<std::endl; 
        if (matrix[playerPos.getY()][playerPos.getX()]->getNeighbour(next_cell)) {
            //Si la prochaine case est une case voisine 
            if (not matrix[playerPos.getY()- next_cell.getY()*2][playerPos.getX()+ next_cell.getX()*2]->occupied()) //if (matrix[playerPos.getY()][playerPos.getX()]->getNeighbour(next_cell)->occupied()) ne fonctionne pas, pouquoi ??? 
                //Si la prochaine case est libre 
                if (not matrix[playerPos.getY()- next_cell.getY()][playerPos.getX()+ next_cell.getX()]->occupied())
                    //Si il n'y a pas de mur entre
                    return true;  
        }
        //TODO: condition saute mouton ("Face à face" dans règles énoncé)
    }
    else if (typeOfMove =="H" || typeOfMove =="V"){
        //TODO :  conditions pour que le coup soit valide
        return true; 
    }
    return false; 
}

bool Board::checkInput(std::string &input, int currentP) {
    if(input.size()!=4){
        return false;
    }
    std::string typeOfMove{input.substr(0,1)};

    Position next_pos{input.substr(2,3)}; 
    next_pos = next_pos*2; //*2 pour avoir la vrai position sur la matrice  
    Position playerPos = players[currentP]->getPawnPos(); 

    if(isValid(typeOfMove, next_pos, playerPos)){ \
        //Si coup valide
        executeMove(typeOfMove, next_pos, currentP); 
        return true;
    }
    return false;
}

void Board::bindCells(){
    for(int i=0;i<boardSize;i+=2){
        for(int j = 0;j<boardSize;j+=2){
            std::vector<std::shared_ptr<MotherCell>> neighbours;
            if(i>0){
                neighbours.push_back(matrix[i-2][j]);
            } else{
                neighbours.push_back(nullptr);
            }
            if(j<boardSize-2){
                neighbours.push_back(matrix[i][j+2]);
            }else{
                neighbours.push_back(nullptr);
            }
            if(i<boardSize-2){
                neighbours.push_back(matrix[i+2][j]);
            } else{
                neighbours.push_back(nullptr);
            }
            if (j>0){
                neighbours.push_back(matrix[i][j-2]);
            } else{
                neighbours.push_back(nullptr);
            }
            matrix[j][i]->setNeighbours(neighbours);
        }
    }
}

void Board:: newGame(){
    boardSize = size*2-1; 
    for (int i = 0; i < size*2-1; i++ ) {
        std::vector<std::shared_ptr<MotherCell> > line;
        for (int j = 0; j<size*2-1; j++){

            //Initialisation des cases: 
            if (( i%2 != 0 and i < boardSize ) or ( j%2 != 0 and j < boardSize))
            { //Si case impaire : Mur 
                line.push_back(std::shared_ptr<WallCell>(new WallCell()));
            } 
            else
            { //Cases Pions
                line.push_back(std::shared_ptr<PawnCell>(new PawnCell()));
            } 

            //Initialisation des pions et joueurs: 
            if (i==10 and j==8)
            {   
                std::shared_ptr<Pawn> pawn1 = std::shared_ptr<Pawn>(new Pawn(Position(8,10)));  
                line[j]->setPiece(std::shared_ptr<Pawn>(pawn1));
                auto player1 = std::shared_ptr<Player>(new Player(0,pawn1));
                players.push_back(player1);
            } 
            if (i==16 and j==8)
            {
                std::shared_ptr<Pawn> pawn2 = std::shared_ptr<Pawn>(new Pawn(Position(8,16))); 
                line[j]->setPiece(std::shared_ptr<Pawn>(pawn2));
                auto player2 = std::shared_ptr<Player>(new Player(1,pawn2));
                players.push_back(player2);
            } 
        }
        matrix.push_back(line);
    }
    bindCells();
}






