#include "Board.hpp"

Board::Board(int size): size{size} {
    newGame(); 
}

void Board::executeMove(Position pos1, Position pos2, int currentP ) {
    std::shared_ptr<Player> player = players[currentP]; 
    player->getPawn()->setPos(pos2); 
    matrix[pos1.getY()*2][pos1.getX()*2]->set(nullptr); 
    matrix[pos2.getY()*2][pos2.getX()*2]->set(player->getPawn()); 

}

bool Board::checkInput(std::string &input, int currentP) {
    if(input.size()!=4){
        std::cout << "size of input: 4 "<<std::endl; //input : d'abord la lettre puis le chiffre
        return false;
    }
    Position pos1{input.substr(0,2)};
    Position pos2{input.substr(2,3)};

    if(pos1 == players[currentP]->getPawn()->getPos()){ 
        //Si la pos initiale de l'input corréspond à la pos du pion

        Position next_cell = Position((-(pos1.getX()-pos2.getX()))%2,(pos1.getY()-pos2.getY())%2); 
        if(matrix[pos2.getX()*2][pos2.getY()*2]->isNeighbour(next_cell)){ //rem: utiliser plutôt .at() pour mat pour éviter les erreures 
            //Si la pos suivante fait bien parti d'un des voisins de la case --> coup valide
            executeMove(pos1, pos2, currentP); 
            return true;
        }
    }
    std::cout<<"move: (ex: i0i1 (i0 = initial position/ i1 = next position)"<<std::endl; 
    return false;
}

bool Board::checkPos(Position pos) const {
    return (pos.getX()>=0 && pos.getY() >= 0 && pos.getX() < boardSize && pos.getY() < boardSize);
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
                std::shared_ptr<Pawn> pawn1 = std::shared_ptr<Pawn>(new Pawn(Position(4,0)));
                line[j]->set(std::shared_ptr<Pawn>(pawn1));
                auto player1 = std::shared_ptr<Player>(new Player(0,pawn1));
                players.push_back(player1);
            } 
            if (i==16 and j==8)
            {
                std::shared_ptr<Pawn> pawn2 = std::shared_ptr<Pawn>(new Pawn(Position(4,8)));
                line[j]->set(std::shared_ptr<Pawn>(pawn2));
                auto player2 = std::shared_ptr<Player>(new Player(1,pawn2));
                players.push_back(player2);
            } 
        }
        matrix.push_back(line);
    }
    bindCells();
}





