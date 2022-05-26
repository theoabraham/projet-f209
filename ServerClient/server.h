#include <pthread.h>
#include "../Quorridor/Model/Gamemodes/DestruQtion.hpp"
#include "../Quorridor/Controller/Game.hpp"
#include "../Quorridor/Model/Board.hpp"
#include "../Quorridor/View/DisplayBoard.hpp"
#include "../DataBase/Database.h"

#include <queue>
#include <string>
#include <vector>

#include "socketlib.h"


using namespace std;

typedef struct {
  string name;
  int socket;
  unsigned version;
  int activeGame = -1;

} user_t;

typedef struct {
  shared_ptr<Board> board;
  shared_ptr<DisplayBoard> displayBoard;
  Game game;
  vector<user_t*> players;
  int activePlayer = 0;
  int neededPlayers = 2;

} game_t;

class Server {
 private:
  Database DB;
  UserInfo UI;
  int max_fd;
  int master_socket;
  vector<user_t*> users;
  vector<game_t*> games;

 private:
  void prepateFDSet(fd_set* read_set);
  void handleSocketReadActivity(fd_set* in_set, int& nactivities);
  void handleNewConnection();
  void disconnectUser(unsigned user_num);
  void forward(message_t* msg, vector<user_t*> receivers);
  void handleMove(string command, int clientSocket);
  void handleCommand(int userIndex, message_t msg);

 public:
  Server();
  void run(int port = 8080);
  void shutDown();

};
