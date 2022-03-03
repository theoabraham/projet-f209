#include <pthread.h>
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
  std::shared_ptr<Board> board = std::shared_ptr<Board>(new Board(2));
  DisplayBoard displayBoard = DisplayBoard(board);
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
  void handleCommand(string command);

 public:
  Server();
  void run(int port = 8080);
  void shutDown();

};
