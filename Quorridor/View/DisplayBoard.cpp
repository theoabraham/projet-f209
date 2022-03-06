#include "DisplayBoard.hpp"

std::string DisplayBoard:: printBoard() const {
      int boardSize = board->getBoardSize(); 
      std::vector<std::vector< std::shared_ptr<MotherCell> > > matrix = board->getMatrix(); 

      std::string stringBoard;

      int l = 0; 
      for(int i=0; i<boardSize;i++){
          std::string currentLine;
          
          if (i%2==0){
           currentLine+=std::to_string(l)+"  "; //Numéro de ligne 
           l++; 
          } else currentLine+="   "; 
          for(int j=0; j<boardSize;j++){
                
              if((i%2==1 and i<boardSize) || (j%2==1 and j<boardSize)){
                  if(matrix[i][j]->occupied()) {
                      if (matrix[i][j]->getPiece()->isHWall())
                        currentLine += "| "; //Mur horizontal 
                      else currentLine+="~ " ; //Mur vertical 
                  } else{
                      currentLine += "  ";
                      //currentLine+=std::to_string(j)+" "; 
                  }
              } else{
                  if(matrix[i][j]->occupied()) {
                      if (board->getNplayer()==2){
                        if (matrix[i][j]->getPiece()->getID() == 0)
                            currentLine += "W "; //Caractère du pion noir 
                        else currentLine += "B "; //Caractère du pion blanc
                      }
                      else {
                          currentLine+= std::to_string(matrix[i][j]->getPiece()->getID()+1);
                          currentLine += " ";  
                      }
 
                  } else{
                      currentLine += "- "; //Caractère de la Case 
                  }
              }
          }
          stringBoard+=currentLine+"\n";
      }

      const std::string alpha{"abcdefghijklmnopqrstuvwxyz"};
      std::string alphaLine;
      alphaLine+= "   ";
      for(int al=0; al<(boardSize/2)+1;al++){  
           alphaLine+=alpha[al]; //Lettre du rang
           alphaLine+="   ";
      }
      stringBoard+=alphaLine+"\n"; 
      std::cout<<stringBoard;
    return stringBoard;
  }

