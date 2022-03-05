#include <queue>
#include <string>
#include <ncurses.h>

#include "../DataBase/Database.h"


using namespace std;

class Client {
 private:
  int socket;
  std::string pseudo;
  WINDOW * boardWindow;
  WINDOW * chatWindow;
  WINDOW * inputWindow;
  bool menuActive = true;

 private:
  int handshake(string ip, int port, string pseudo);
  static void* manageInputs(void* instance);
  void manageInputs();
  void manageSocketTraffic();

 public:
  Client();
  void run(string pseudo, string ip, int port = 8080);
};