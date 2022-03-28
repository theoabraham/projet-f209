#include <queue>
#include <string>
#include "WindowNC.hpp"

#include "../DataBase/Database(old).h"


using namespace std;

class Client {
 private:
  int socket;
  int line_counter=0;
  char gameMode[8] = "C\0";
  WindowNC view = WindowNC();

 private:
  int handshake(string ip, int port, string pseudo, string mdp);
  static void* manageInputs(void* instance);
  void manageInputs();
  void manageSocketTraffic();
  void fetchInput(char &buffer);
  void displayMenu(std::vector<const char*> options);
  void clearWindow(WINDOW * window);

 public:
  Client();
  void runGame(string pseudo, string mdp, string ip, int port = 8080);
  void runMenu(string ip, int port);
};