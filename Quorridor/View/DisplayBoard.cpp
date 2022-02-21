#include "DisplayBoard.hpp"

void DisplayBoard:: printBoard() const {
      int boardSize = board->getBoardSize(); 
      std::vector<std::vector< std::shared_ptr<MotherCell> > > matrix = board->getMatrix(); 

      std::string stringBoard;
             
      for(int i=0; i<boardSize;i++){
          std::string currentLine;
          if (i<10) currentLine += std::to_string(i)+" | ";
          else currentLine += std::to_string(i)+"| ";
          for(int j=0; j<boardSize;j++){
                
              if((i%2==1 and i<boardSize) or (j%2==1 and j<boardSize)){
                  if(matrix[i][j]->occupied()) {
                      currentLine += "W ";
                  } else{
                      currentLine += "  ";
                  }
              } else{
                  if(matrix[i][j]->occupied()) {
                      currentLine += "\u265F "; //Caractère du pion 
                  } else{
                      currentLine += "\u2610 "; //Case 
                  }
              }
          }
          stringBoard+=currentLine+"\n";
      }
      std::cout<<stringBoard;
  }

//push branche spécifique : git push origin "branchName"