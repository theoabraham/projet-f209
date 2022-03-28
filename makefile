FLAGS=-Wall -Werror -std=c++17 -g 

all: client server

client: ServerClient/client.cpp ServerClient/socketlib.o ServerClient/client.h ServerClient/WindowNC.hpp
	g++ $(DATABASE) -o client ServerClient/client.cpp ServerClient/socketlib.o ServerClient/socketlib.h ServerClient/client.h ServerClient/WindowNC.hpp ${FLAGS} -pthread -lncursesw

server: ServerClient/server.cpp $(MODEL) $(GAMEMODES) $(VIEW) $(CONTROLLER) ServerClient/socketlib.o ServerClient/server.h
	g++ $(MODEL) $(GAMEMODES) $(VIEW) $(CONTROLLER) -g -o server ServerClient/server.cpp ServerClient/socketlib.o ServerClient/socketlib.h ${FLAGS}

socketlib.o: socketlib.cpp socketlib.h
	g++ -c socketlib.cpp ${FLAGS}

MODEL = Quorridor/Model/Board.cpp Quorridor/Model/Board.hpp Quorridor/Model/MotherCell.hpp Quorridor/Model/MotherCell.cpp Quorridor/Model/Piece.hpp Quorridor/Model/Player.hpp Quorridor/Model/Position.hpp Quorridor/Model/Position.cpp

GAMEMODES = Quorridor/Model/Gamemodes/DestruQtion.cpp Quorridor/Model/Gamemodes/DestruQtion.hpp Quorridor/Model/Gamemodes/QQQuoridor.cpp Quorridor/Model/Gamemodes/QQQuoridor.hpp

VIEW = Quorridor/View/DisplayBoard.cpp Quorridor/View/DisplayBoard.hpp

CONTROLLER = Quorridor/Controller/Game.cpp Quorridor/Controller/Game.hpp

DATABASE = DataBase/Database.cpp DataBase/Database.h

clean:
	rm -f client server *.o

clear: clean