#include "Board.hpp"

Board::Board(int size): size{size} {
    newGame(); 
}

void Board::bindCells(){
    for(int i=0;i<boardSize;i+=2){

        for(int j = 0;j<boardSize;j+=2){
            std::vector<std::shared_ptr<MotherCell>> neighbours;
            if(i>0){
                neighbours.push_back(&matrix[i-2][j]);
            } else{
                neighbours.push_back(nullptr);
            }
            if(j<boardSize-2){
                neighbours.push_back(&matrix[i][j+2]);
            }else{
                neighbours.push_back(nullptr);
            }
            if(i<boardSize-2){
                neighbours.push_back(&matrix[i+2][j]);
            } else{
                neighbours.push_back(nullptr);
            }
            if (j>0){
                neighbours.push_back(&matrix[i][j-2]);
            } else{
                neighbours.push_back(nullptr);
            }
            matrix[i][j].setNeighbours(neighbours);
        }

    }
}

void Board:: newGame(int nPlayer){

    boardSize = size*2-1; 
    for (int i = 0; i < size*2-1; i++ ) {
        std::vector<MotherCell> line;
        
        for (int j = 0; j<size*2-1; j++){
            if (( i%2 != 0 and i < boardSize ) or ( j%2 != 0 and j < boardSize)){ //si case impaire --> Murs 
                line.push_back(WallCell());
            } else{ //Cases
                line.push_back(PawnCell());
            } 

            if (i==0 and j==8){
                std::shared_ptr<Pawn> pawn1 = std::shared_ptr<Pawn>(new Pawn(Position(8,0)));
                line[j].set(std::shared_ptr<Pawn>(pawn1));
                auto player1 = std::shared_ptr<Player>(new Player(pawn1, 0));
                players.push_back(player1);
            } 

            if (i==16 and j==8){
                std::shared_ptr<Pawn> pawn2 = std::shared_ptr<Pawn>(new Pawn(Position(8,16)));
                line[j].set(std::shared_ptr<Pawn>(pawn2));
                auto player2 = std::shared_ptr<Player>(new Player(pawn2, 1));
                players.push_back(player2);
            } 
        }
        matrix.push_back(line);
    }
    bindCells();
}

void Board::ExecuteMove(std::string& input) {
    if(checkInput(input)){
        std::cout << "all good"<<std::endl;
    }
}

bool Board::checkInput(std::string &input) {
    std::cout<<"Checking input " << input << std::endl;
    if(input.size()!=4){
        std::cout << "input too long "<<std::endl;
        return false;
    }
    Position pos1{input.substr(0,2)};
    std::cout<<input.substr(0,2)<<std::endl;
    Position pos2{input.substr(2,3)};
    std::cout<<input.substr(2,3)<<std::endl;
    std::cout<<"Position 1 : "<< pos1.getX() << " " << pos1.getY()<<std::endl;
    std::cout<<"Position 2 : "<< pos2.getX() << " " << pos2.getY()<<std::endl;
    if(pos1 == players[currentPlayer]->getPawn()->getPos()){
        std::cout << "check 1"<<std::endl;
        std::cout<<-(pos1.getX()-pos2.getX()) << " " <<pos1.getY()-pos2.getY()<<std::endl;
        if(matrix[pos2.getX()][pos2.getY()].isNeighbour(Position((-(pos1.getX()-pos2.getX()))%2,(pos1.getY()-pos2.getY())%2))){
            std::cout << "check 2"<<std::endl;
            return true;
        }
    }
    return false;
}

bool Board::checkPos(Position pos) const {
    return (pos.getX()>=0 && pos.getY() >= 0 && pos.getX() < boardSize && pos.getY() < boardSize);
}

MotherCell Board::operator[](const Position &other) {
    return matrix[other.getX()][other.getY()];
}





