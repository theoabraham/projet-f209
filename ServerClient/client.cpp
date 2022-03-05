#include "client.h"

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#include "socketlib.h"

//using namespace std;

Client::Client() {
  initscr();
  cbreak();

  int maxX, maxY;
  getmaxyx(stdscr, maxY, maxX);
  clear();

  boardWindow = newwin(2*maxY/3, maxX/2, 0, 0);
  chatWindow = newwin(2*maxY/3, maxX/2, 0, maxX/2 + 1);
  inputWindow = newwin(maxY/3, maxX, 2*maxY/3, 0);
  refresh();
  box(boardWindow, 0, 0);
  box(chatWindow, 0, 0);
  box(inputWindow, 0, 0);
  wrefresh(boardWindow);
  wrefresh(chatWindow);
  wrefresh(inputWindow);
}

void Client::run(string pseudo, string ip, int port) {
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
  write(STDOUT_FILENO, ">> ", 3);
  while (mvwgetstr(inputWindow, 1, 1, buffer) == 0) {
    buffer[strlen(buffer)] = '\0';
    message_t msg = {.timestamp = time(NULL), .message = string(buffer)};
    werase(inputWindow);
    box(inputWindow, 0, 0);
    wrefresh(inputWindow);
    if (ssend(this->socket, &msg) <= 0) {
      exit(0);
    }
    write(STDOUT_FILENO, ">> ", 3);
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
      mvwprintw(chatWindow, y+1, 1, msg.message.c_str());
      getyx(chatWindow, y, x);
      wrefresh(chatWindow);
      y += 1;
    } else {
      werase(boardWindow);
      box(boardWindow, 0, 0);
      mvwprintw(boardWindow, 1, 1, msg.message.c_str());
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
  const std::string  ip = "127.0.0.1";
  
  //if (argc > 2) {
  //  ip = argv[2];
  //}
  Client client = Client();
  std::string pseudo = "Hatapon";
  client.run(pseudo, ip.c_str(), port);
  return 0;
}