#include <queue>
#include <string>
#include <ncurses.h>
#include <locale.h>

#include "../DataBase/Database.h"


using namespace std;

class Client {
 private:
  int socket;
  int line_counter=0;
  char pseudo[80];
  WINDOW * boardWindow;
  WINDOW * boardBoxWindow;
  WINDOW * chatWindow;
  WINDOW * inputWindow;

 private:
  int handshake(string ip, int port, string pseudo);
  static void* manageInputs(void* instance);
  void manageInputs();
  void manageSocketTraffic();
  void fetchInput(char &buffer);
  void loginRoutine();
  void connectRoutine(DatabaseHandler *dbh);

 public:
  Client();
  void runGame(string pseudo, string ip, int port = 8080);
  void runMenu(string ip, int port);
};