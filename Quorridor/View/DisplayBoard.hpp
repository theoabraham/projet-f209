#include <memory>
#include <vector>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "../Model/Board.hpp"
#include "../Model/MotherCell.hpp"


#ifndef DISPLAYBOARD_HPP
#define DISPLAYBOARD_HPP

class DisplayBoard {
  const std::shared_ptr<Board> board;
 public:

  DisplayBoard(const std::shared_ptr< Board> board): board{board} {};
  DisplayBoard(){};
  /**
   *Imprime le plateau de jeux avec ces pions et murs sur le terminal 
  */ 
  std::string printBoard() const ; 
}; 

#endif 