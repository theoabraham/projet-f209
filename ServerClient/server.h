#include <pthread.h>
#include "../Quorridor/Model/Gamemodes/DestruQtion.hpp"
#include "../Quorridor/Controller/Game.hpp"
#include "../Quorridor/Model/Board.hpp"
#include "../Quorridor/View/DisplayBoard.hpp"

#include <queue>
#include <string>
#include <vector>

#include "socketlib.h"


using namespace std;

typedef struct {
  string name;
  int socket;
  unsigned version;

} user_t;

class Server {
 private:
  int max_fd;
  int master_socket;
  vector<user_t*> users;
  shared_ptr<Board> board = shared_ptr<Board>(new DestruQtionBoard(2));
  shared_ptr<DisplayBoard> displayBoard = shared_ptr<DisplayBoard>(new DisplayBoard(board));  
  Game game = Game(board, displayBoard);
  int activePlayer = 0;
  int registeredPlayers = 0;
  int neededPlayers = 2;

 private:
  void prepateFDSet(fd_set* read_set);
  void handleSocketReadActivity(fd_set* in_set, int& nactivities);
  void handleNewConnection();
  void disconnectUser(unsigned user_num);
  void forward(message_t* msg);
  void handleCommand(string command, int clientSocket);

 public:
  Server();
  void run(int port = 8080);
  void shutDown();

};
