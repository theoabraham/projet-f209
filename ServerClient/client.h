#include <queue>
#include <string>
#include "../menus/menuOptions.hpp"
using namespace std;

class Client {
 private:
  int socket;


 private:
  int handshake(string ip, int port, string pseudo);
  static void* manageInputs(void* instance);
  void manageInputs();
  void manageSocketTraffic();

 public:
  Client();
  void runMenu();
  void runGame(string pseudo, string ip, int port = 8080);
};