FLAGS = -Wall -std=c++17 -g 

MODEL = Model/Board.cpp Model/Board.hpp Model/MotherCell.hpp Model/MotherCell.cpp Model/Piece.hpp Model/Player.hpp Model/Position.hpp Model/Position.cpp

GAMEMODES = Model/Gamemodes/DestruQtion.cpp Model/Gamemodes/DestruQtion.hpp Model/Gamemodes/QQQuoridor.cpp Model/Gamemodes/QQQuoridor.hpp Model/Gamemodes/Minos.cpp Model/Gamemodes/Minos.hpp

VIEW = View/DisplayBoard.cpp View/DisplayBoard.hpp

CONTROLLER = Controller/Game.cpp Controller/Game.hpp 

all: Quoridor

Quoridor: $(MODEL) $(GAMEMODES) $(VIEW) $(CONTROLLER) main.cpp  
	g++ $(MODEL) $(GAMEMODES) $(VIEW) $(CONTROLLER) main.cpp  -o main $(FLAGS)