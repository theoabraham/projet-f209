#include "Board.hpp"

Board::Board(int size): size{size} {
    newGame(); 
}

void Board::executeMove(std::string &typeOfMove, Position &pos, int currentP ) { 
    Position playerPos = players[currentP]->getPawnPos();
    players[currentP]->setPawnPos(pos);

    matrix[playerPos.getY()][playerPos.getX()]->setPiece(nullptr); 
    matrix[pos.getY()][pos.getX()]->setPiece(players[currentP]->getPawn()); 
}

bool Board::isValid(std::string &typeOfMove, Position &next_pos, Position &playerPos){
    if (typeOfMove=="P" || typeOfMove=="H" || typeOfMove=="V"){
        Position next_cell = Position((-(playerPos.getX()-next_pos.getX())),(playerPos.getY())-next_pos.getY());
        if (matrix[playerPos.getX()][playerPos.getY()]->isNeighbour(next_cell)) return true; 
    }  
    return false; 
}

bool Board::checkInput(std::string &input, int currentP) {
    if(input.size()!=4){
        std::cout<<"Format: (ex: P e1) " <<std::endl<< "1.Type of move: P (pawn), H (horizontal Wall), V (vertical wall)" <<std::endl<< "2.move: cell number" <<std::endl;
        return false;
    }
    std::string typeOfMove{input.substr(0,1)};

    Position next_pos{input.substr(2,3)}; 
    next_pos = next_pos*2; //*2 pour avoir la vrai position sur la matrice  

    Position playerPos = players[currentP]->getPawnPos(); 

    if(isValid(typeOfMove, next_pos, playerPos)){ 
        executeMove(typeOfMove, next_pos, currentP); 
        return true;
    }
    std::cout<<"Format: (ex: P e1) " <<std::endl<< "1.Type of move: P (pawn), H (horizontal Wall), V (vertical wall)" <<std::endl<< "2.move: cell number" <<std::endl;
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
            matrix[i][j]->setNeighbours(neighbours);
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
            if (i==0 and j==8)
            {   
                std::shared_ptr<Pawn> pawn1 = std::shared_ptr<Pawn>(new Pawn(Position(8,0)));  //changer en Position(8,0) 
                line[j]->setPiece(std::shared_ptr<Pawn>(pawn1));
                auto player1 = std::shared_ptr<Player>(new Player(0,pawn1));
                players.push_back(player1);
            } 
            if (i==16 and j==8)
            {
                std::shared_ptr<Pawn> pawn2 = std::shared_ptr<Pawn>(new Pawn(Position(8,16))); //changer en Position(8,16) 
                line[j]->setPiece(std::shared_ptr<Pawn>(pawn2));
                auto player2 = std::shared_ptr<Player>(new Player(1,pawn2));
                players.push_back(player2);
            } 
        }
        matrix.push_back(line);
    }
    bindCells();
}






