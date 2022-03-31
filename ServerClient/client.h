#include <queue>
#include <string>
#include <iostream>

#include "../Quorridor/View/Interface/menuwindow.h"
#include "WindowNC.hpp"

using namespace std;

class Client {
 private:
  int socket;
  int line_counter=0;
  char gameMode[8] = "C\0";
  char numberPlayers[8] = "2\0";
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
  void runMenu(string pseudo, string mdp, string ip, int port);
};
