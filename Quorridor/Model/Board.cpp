#include "Board.hpp"

Board::Board(int size): size{size} {
    newGame(); 
}

void Board::bindCells(){}

void Board:: newGame(int nPlayer){

    std::shared_ptr<Pawn> pawn1 = std::shared_ptr<Pawn>(new Pawn());
    std::shared_ptr<Pawn> pawn2 = std::shared_ptr<Pawn>(new Pawn());

    Player player1 = Player(pawn1); 
    Player player2 = Player(pawn2); 

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
                std::shared_ptr<Pawn> pawn1 = std::shared_ptr<Pawn>(new Pawn());
                line[j].set(std::shared_ptr<Pawn>(new Pawn())); 
                Player player1 = Player(pawn1); 
            } 

            if (i==16 and j==8){
                std::shared_ptr<Pawn> pawn2 = std::shared_ptr<Pawn>(new Pawn());
                line[j].set(std::shared_ptr<Pawn>(pawn2)); 
                Player player2 = Player(pawn2); 
            } 
        }
        matrix.push_back(line);
    }
    bindCells();
}

