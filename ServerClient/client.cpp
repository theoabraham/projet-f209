#include "client.h"

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "socketlib.h"

//using namespace std;

Client::Client() {
}

void Client::runMenu(string pseudo, string mdp, string ip, int port){
  keypad(view.inputWindow, TRUE);
  //std::vector<const char*> basicOptions = {"Option :", "(P)lay", "Choose (G)amemode"};
  //std::vector<const char*> gameModeOptions = {"(C)lassic", "(D)estruQtion", "(Q)QQuorridor"};
  while(true){
    char menuChoice;
    view.displayMenu({"Option :", "(P)lay", "Chose (N)umber of players", "Chose (G)amemode"});
    view.fetchInput(menuChoice);
    if (menuChoice == 'P'){
      this->runGame(pseudo, mdp, ip.c_str(), port);
      message_t _;
      _.message = "/Play";
      ssend(this->socket, &_);
    }
    if (menuChoice == 'N') {
      view.displayMenu({"(2) joueurs", "(4) joueurs", "Certains modes ne permettent que 4 joueurs"});
      view.fetchInput(*numberPlayers);
      this->gameMode[strlen(numberPlayers)]='\0';
      while (strcmp(numberPlayers, "2\0") != 0 && strcmp(numberPlayers, "4\0") != 0) {
        view.clearWindow(view.chatBoxWindow);
        mvwprintw(view.chatWindow, 3, 0, "Wrong input, please enter 2 or 4.");
        wrefresh(view.chatWindow);
        view.fetchInput(*numberPlayers);
        this->numberPlayers[strlen(numberPlayers)]='\0';
      }
    }
    if (menuChoice == 'G'){
      view.displayMenu({"(C)lassic", "(D)estruQtion", "(Q)QQuorridor"});
      view.fetchInput(*gameMode);
      this->gameMode[strlen(gameMode)]='\0';
      while (strcmp(gameMode, "C\0") != 0 && strcmp(gameMode, "D\0") != 0 && strcmp(gameMode, "Q\0") != 0) {
        view.clearWindow(view.chatBoxWindow);
        mvwprintw(view.chatWindow, 3, 0, "Wrong input, please enter C, D or Q.");
        wrefresh(view.chatWindow);
        view.fetchInput(*gameMode);
        this->gameMode[strlen(gameMode)]='\0';
      }
    }
  }
}

void Client::runGame(string pseudo, string mdp, string ip, int port) {
  //Le client se connecte au serveur, et créé un thread pour gérer la reception de messages.
  werase(view.chatWindow);
  wrefresh(view.chatWindow);
  this->socket = this->handshake(ip, port, pseudo, mdp);
  pthread_t tid;
  pthread_create(&tid, nullptr, Client::manageInputs, this);
  this->manageSocketTraffic();
  close(this->socket);
}

void *Client::manageInputs(void *instance) {
  //Version void* de manage input pour pouvoir creer le thread
  Client *c = (Client *)instance;
  c->manageInputs();
  return nullptr;
}

void Client::manageInputs() {
  // Le client peut ecrire et envoyer ses messages
  char buffer[1024];
  while (true) {
    view.fetchInput(*buffer);
    buffer[strlen(buffer)] = '\0';
    message_t msg = {.timestamp = time(NULL), .message = string(buffer)};
    werase(view.inputWindow);
    box(view.inputWindow, 0, 0);
    wrefresh(view.inputWindow);
    if (ssend(this->socket, &msg) <0) {
      exit(0);
    }
  }
  close(this->socket);
  exit(0);
}

void Client::manageSocketTraffic() {
  //Reception des messages via le serveur
  int x = 1;
  int y = 0;
  while (true) {
    message_t msg;
    size_t nbytes = receive(this->socket, &msg);
    if (nbytes <= 0) {
      exit(0);
    }
    if (msg.message.substr(0,1) == (string)"["){
      mvwprintw(view.chatWindow, y+1, 1, msg.message.c_str());
      getyx(view.chatWindow, y, x);
      wrefresh(view.chatWindow);
    } else {
      mvwprintw(view.boardWindow, 0, 0, msg.message.c_str());
      wrefresh(view.boardWindow);
    }
  }
}

int Client::handshake(string ip, int port, string pseudo, string mdp) {
  int socket = checked(create_socket());
  if (connect_socket(socket, "127.0.0.1", port) < 0) {
    exit(1);
  }
  // Send username
  if (safe_write(socket, pseudo.c_str(), pseudo.length()) <= 0) {
    exit(1);
  }
  // Send password
  if (safe_write(socket, mdp.c_str(), mdp.length()) <= 0) {
    exit(1);
  }
  // Receive acknowledgement
  int ack;
  if (safe_read(socket, &ack, sizeof(int)) <= 0) {
    exit(1);
  }
  if (ack != 0) {
    std::cout<<"Connection rejected by server\n";
    exit(1);
  }
  return socket;
}

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Utilisation: ./client <port> [<ip>]\n");
    exit(0);
  }
  const int port = atoi(argv[1]);
  if (port < 1024) {
    fprintf(stderr, "Le port doit être supérieur à 1023.\n");
    exit(0);
  }
  std::string ip;
  if (argc > 2) {
    ip = argv[2];
  }

  char pseudo[64];
  cin.getline(pseudo, 64);
  char mdp[16];
  cin.getline(mdp, 16);
  Client client = Client();
  client.runMenu(pseudo, mdp, ip.c_str(), port);
  return 0;
}