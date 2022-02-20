#include "Board.hpp"

Board::Board(int nsize):size{nsize}, boardSize(nsize*2-1){
    for(int i=0; i<size*2-1; i++){
        std::vector<MotherCell> line;
        for(int j = 0; j<size*2-1; j++){
            if((i%2!=0 and i<boardSize)or(j%2!=0 and j<boardSize)){
                line.push_back(WallCell());
            } else{
                line.push_back(PawnCell());
            }
        }
        matrix.push_back(line);
    }
    bindCells();
}

void Board::printBoard(){
    std::string stringBoard;
    for(int i=0; i<boardSize;i++){
        std::string currentLine;
        currentLine += std::to_string(i)+"| ";
        for(int j=0; j<boardSize;j++){

            if((i%2==1 and i<boardSize) or (j%2==1 and j<boardSize)){
                if(matrix[i][j].occupied()) {
                    currentLine += "W ";
                } else{
                    currentLine += "  ";
                }
            } else{
                if(matrix[i][j].occupied()) {
                    currentLine += "P ";
                } else{
                    currentLine += "0 ";
                }
            }
        }
        stringBoard+=currentLine+"\n";
    }
    std::cout<<stringBoard;
}

void Board::bindCells(){

}

