#include "client.h"

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "socketlib.h"

//using namespace std;

Client::Client() {
}

void Client::runMenu(string ip, int port){
  /*
  keypad(inputWindow, TRUE);
  // std::vector<const char*> basicOptions = {"Option :", "(L)ogin and Play", "Choose (G)amemode"};
  std::vector<const char*> gameModeOptions = {"(C)lassic", "(D)estruQtion", "(Q)QQuorridor"};
  while(true){
    char menuChoice;
    this->displayMenu({"Option :", "(L)ogin and Play", "Chose (G)amemode"});
    this->fetchInput(menuChoice);
    if (menuChoice == 'L'){
      this->loginRoutine();
      DatabaseHandler dbh(pseudo);
      this->connectRoutine(&dbh);
      this->runGame(pseudo, ip, port);
    } else if (menuChoice == 'G'){
      this->displayMenu(gameModeOptions);
      this->fetchInput(*gameMode);
      this->gameMode[strlen(gameMode)]='\0';
      while (strcmp(gameMode, "C\0") != 0 && strcmp(gameMode, "D\0") != 0 && strcmp(gameMode, "Q\0") != 0) {
        mvwprintw(chatWindow, 3, 0, "Wrong input, please enter C, D or Q.");
        wrefresh(chatWindow);
        this->fetchInput(*gameMode);
        this->gameMode[strlen(gameMode)]='\0';
      }
    }
  }
  */
  std::cout<<"le menu tourne"<<std::endl;
}

void Client::runGame(string pseudo, string ip, int port) {
  //Le client se connecte au serveur, et créé un thread pour gérer la reception de messages.
  werase(view.chatWindow);
  wrefresh(view.chatWindow);
  this->socket = this->handshake(ip, port, pseudo);
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
    mvwgetstr(view.inputWindow, 1, 1, buffer);
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

int Client::handshake(string ip, int port, string pseudo) {
  int socket = checked(create_socket());
  if (connect_socket(socket, "127.0.0.1", port) < 0) {
    exit(1);
  }
  // Send username
  if (safe_write(socket, pseudo.c_str(), pseudo.length()) <= 0) {
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
  Client client = Client();
  client.runGame("test", ip.c_str(), port);
  return 0;
}