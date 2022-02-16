FLAGS = -Wall -Wextra -std=c++17 -g 

MODEL = Model/Board.cpp Model/Board.h Model/MotherCell.hpp Model/MotherCell.cpp Model/Item.cpp Model/Item.h Model/PawnCell.h Model/PawnCell.cpp Model/WallCell.h Model/WallCell.cpp

VIEW = View/DisplayBoard.cpp View/DisplayBoard.hpp

all: Quoridor

Quoridor: $(MODEL) $(VIEW) main.cpp  
	g++ $(MODEL) $(VIEW) main.cpp  -o main $(FLAGS)