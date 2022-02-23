#include "DisplayBoard.hpp"

void DisplayBoard:: printBoard() const {
    /*
    Imprime le plateau de jeux avec ces pions et murs sur le terminal 
    */
      int boardSize = board->getBoardSize(); 
      std::vector<std::vector< std::shared_ptr<MotherCell> > > matrix = board->getMatrix(); 

      const std::string alpha{"abcdefghijklmnopqrstuvwxyz"};
      std::string stringBoard;

      std::string alphaLine;
      alphaLine+= "   ";
      for(int al=0; al<boardSize;al++){  
           alphaLine+=alpha[al]; //Lettre du rang
           alphaLine+=" ";           
      }
      stringBoard+=alphaLine+"\n"; 

      for(int i=0; i<boardSize;i++){
          std::string currentLine;
          currentLine+=(i<10)?std::to_string(i)+"  ": std::to_string(i)+" "; //Numéro de ligne

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
                      currentLine += "\u2610 "; //Caractère de la Case 
                  }
              }
          }
          stringBoard+=currentLine+"\n";
      }
      std::cout<<stringBoard;
  }

//push branche spécifique : git push origin "branchName"


