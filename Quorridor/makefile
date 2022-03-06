FLAGS = -Wall -std=c++17 -g 

MODEL = Model/Board.cpp Model/Board.hpp Model/MotherCell.hpp Model/MotherCell.cpp Model/Piece.hpp Model/Player.hpp Model/Position.hpp Model/Position.cpp Model/Gamemodes/DestruQtion.cpp Model/Gamemodes/DestruQtion.hpp

VIEW = View/DisplayBoard.cpp View/DisplayBoard.hpp

CONTROLLER = Controller/Game.cpp Controller/Game.hpp 

all: Quoridor

Quoridor: $(MODEL) $(VIEW) $(CONTROLLER) main.cpp  
	g++ $(MODEL) $(VIEW) $(CONTROLLER) main.cpp  -o main $(FLAGS)