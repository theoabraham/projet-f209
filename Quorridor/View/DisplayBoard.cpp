#include "DisplayBoard.hpp"

void DisplayBoard:: printBoard() const {
    /*
    Imprime le plateau de jeux avec ces pions et murs sur le terminal 
    */
      int boardSize = board->getBoardSize(); 
      std::vector<std::vector< std::shared_ptr<MotherCell> > > matrix = board->getMatrix(); 

      std::string stringBoard;

      int l = 0; 
      for(int i=0; i<boardSize;i++){
          std::string currentLine;
          
          if (i%2==0){
           currentLine+=std::to_string(l)+"  "; //Numéro de ligne 
           l++; 
          }
          for(int j=0; j<boardSize;j++){
                
              if((i%2==1 and i<boardSize) or (j%2==1 and j<boardSize)){
                  if(matrix[i][j]->occupied()) {
                      currentLine += "\u25AC "; //Mur horizontal 
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

      const std::string alpha{"abcdefghijklmnopqrstuvwxyz"};
      std::string alphaLine;
      alphaLine+= "   ";
      for(int al=0; al<(boardSize/2)+1;al++){  
           alphaLine+=alpha[al]; //Lettre du rang
           alphaLine+="   ";           
      }
      stringBoard+=alphaLine+"\n"; 

      std::cout<<stringBoard;
  }

//push branche spécifique : git push origin "branchName"


