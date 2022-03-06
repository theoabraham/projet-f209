FLAGS=-Wall -Werror -std=c++17 -g 

all: client server

client: client.cpp socketlib.o client.h
	g++ $(DATABASE) -o client client.cpp socketlib.o socketlib.h client.h ${FLAGS} -pthread

server: server.cpp $(MODEL) ${GAMEMODES} $(VIEW) $(CONTROLLER) socketlib.o server.h
	g++ $(MODEL) $(VIEW) $(CONTROLLER) -g -o server server.cpp socketlib.o socketlib.h ${FLAGS}

socketlib.o: socketlib.cpp socketlib.h
	g++ -c socketlib.cpp ${FLAGS}

MODEL = ../Quorridor/Model/Board.cpp ../Quorridor/Model/Board.hpp ../Quorridor/Model/MotherCell.hpp ../Quorridor/Model/MotherCell.cpp ../Quorridor/Model/Piece.hpp ../Quorridor/Model/Player.hpp ../Quorridor/Model/Position.hpp ../Quorridor/Model/Position.cpp

GAMEMODES = ../Quorridor/Model/Gamemodes/DestruQtion.cpp ../Quorridor/Model/Gamemodes/DestruQtion.hpp

VIEW = ../Quorridor/View/DisplayBoard.cpp ../Quorridor/View/DisplayBoard.hpp

CONTROLLER = ../Quorridor/Controller/Game.cpp ../Quorridor/Controller/Game.hpp

DATABASE = ../DataBase/Database.cpp ../DataBase/Database.h

clean:
	rm -f client server *.o

clear: clean