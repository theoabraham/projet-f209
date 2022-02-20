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

  void printBoard() const ; 
}; 

#endif 