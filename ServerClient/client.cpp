#include "client.h"

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "socketlib.h"

//using namespace std;

Client::Client() {
  setlocale(LC_ALL, "");
  initscr();
  cbreak();

  int maxX, maxY;
  getmaxyx(stdscr, maxY, maxX);
  clear();

  boardBoxWindow = newwin(2*maxY/3, maxX/2, 0, 0);
  boardWindow = newwin(2*maxY/3 - 2, maxX/2 - 2, 1, 1);
  chatWindow = newwin(2*maxY/3, maxX/2, 0, maxX/2 + 1);
  inputWindow = newwin(maxY/3, maxX, 2*maxY/3, 0);
  refresh();
  box(boardBoxWindow, 0, 0);
  box(chatWindow, 0, 0);
  box(inputWindow, 0, 0);
  wrefresh(boardBoxWindow);
  wrefresh(chatWindow);
  wrefresh(inputWindow);
}

void Client::runMenu(string ip, int port){
  this->loginRoutine();
  this->runGame(pseudo, ip, port);
}

void Client::loginRoutine(){
  int y = 1;
  char Mdp;
  char answer;
  const char *askFileMsg = "Entrez un pseudo";
  const char *askFileCreation = "Vouslez vous creer un compte?";
  mvwprintw(chatWindow, y, 1, askFileMsg); //Print dans la fenetre chatwindow en position y=1, x=1, le message askFileMsg
  wrefresh(chatWindow);
  this->fetchInput(*pseudo);
  this->pseudo[strlen(pseudo)] = '\0';
  if (DatabaseHandler::isStringValid(pseudo)){
    if (!DatabaseHandler::does_file_exist(pseudo)){
      y++;
      mvwprintw(chatWindow, y, 1, askFileCreation);
      wrefresh(chatWindow);
      this->fetchInput(answer);
      } else {
        DatabaseHandler dbh = DatabaseHandler(&pseudo);
      }
    }
    this->fetchInput(Mdp);
    if (dbh.checkPswd(&Mdp))
  }

void Client::runGame(string pseudo, string ip, int port) {
  //Le client se connecte au serveur, et créé un thread pour gérer la reception de messages.
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
    mvwgetstr(inputWindow, 1, 1, buffer);
    buffer[strlen(buffer)] = '\0';
    message_t msg = {.timestamp = time(NULL), .message = string(buffer)};
    werase(inputWindow);
    box(inputWindow, 0, 0);
    wrefresh(inputWindow);
    if (ssend(this->socket, &msg) <0) {
      exit(0);
    }
  }
  close(this->socket);
  exit(0);
}

void Client::fetchInput(char &buffer){ //Passage par reference pour que le contenu de buffer soit accessible dans d'autres fonctions.
  mvwgetstr(inputWindow, 1, 1, &buffer); //Récupère l'input dans inputWindow et stocke le contenu dans buffer
  werase(inputWindow);
  box(inputWindow, 0, 0);
  wrefresh(inputWindow);
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
      mvwprintw(chatWindow, y+1, 1, msg.message.c_str());
      getyx(chatWindow, y, x);
      wrefresh(chatWindow);
    } else {
      mvwprintw(boardWindow, 0, 0, msg.message.c_str());
      wrefresh(boardWindow);
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
  client.runMenu(ip.c_str(), port);
  return 0;

}