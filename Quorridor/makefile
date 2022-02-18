FLAGS = -Wall -Wextra -std=c++17 -g 

MODEL = Model/Board.cpp Model/Board.hpp Model/MotherCell.hpp Model/MotherCell.cpp Model/Piece.cpp Model/Piece.hpp Model/Player.cpp Model/Player.hpp

VIEW = View/DisplayBoard.cpp View/DisplayBoard.hpp

all: Quoridor

Quoridor: $(MODEL) $(VIEW) main.cpp  
	g++ $(MODEL) $(VIEW) main.cpp  -o main $(FLAGS)