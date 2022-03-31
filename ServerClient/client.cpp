#include "client.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "socketlib.h"


Client::Client() {

//constructeur, prend le style d'affichage en paramètre,
//a besoin d'un if(){}

}


void Client::runMenu(string pseudo, string mdp, string ip, int port){
  keypad(view.inputWindow, TRUE);
  bool _ = true;
  while(_){
    char menuChoice;
    view.displayMenu({"Option :", "(P)lay", "Chose (N)umber of players", "Chose (G)amemode"}); //options de base
    view.fetchInput(menuChoice); //demande un choix a l'utilisateur
    if (menuChoice == 'P'){ //les choix prennent la forme de lettres majuscules.
      _ = false;
    }
    if (menuChoice == 'N') {
      view.displayMenu({"(2) joueurs", "(4) joueurs", "Certains modes ne permettent que 4 joueurs"}); //options de nombre de joueurs
      view.fetchInput(*numberPlayers);
      while (strcmp(numberPlayers, "2") != 0 && strcmp(numberPlayers, "4") != 0) { //tant que la réponse n'est pas correcte : 
        view.clearWindow(view.chatBoxWindow);
        mvwprintw(view.chatWindow, 3, 0, "Wrong input, please enter 2 or 4.");
        wrefresh(view.chatWindow);
        view.fetchInput(*numberPlayers);
      }
      this->numberPlayers[strlen(numberPlayers)]='\0';
    }
    if (menuChoice == 'G'){
      view.displayMenu({"(C)lassic", "(D)estruQtion", "(Q)QQuorridor"}); //options de mode de jeu
      view.fetchInput(*gameMode);
      while (strcmp(gameMode, "C") != 0 && strcmp(gameMode, "D") != 0 && strcmp(gameMode, "Q") != 0) { //tant que la réponse n'est pas correcte : 
        view.clearWindow(view.chatBoxWindow);
        mvwprintw(view.chatWindow, 3, 0, "Wrong input, please enter C, D or Q.");
        wrefresh(view.chatWindow);
        view.fetchInput(*gameMode);
      }
      this->gameMode[strlen(gameMode)]='\0';
    }
  }
  this->runGame(pseudo, mdp, ip, port); //normalement, lance le jeu, mais la ca bug si on le lance d'ici...
}

void Client::runGame(string pseudo, string mdp, string ip, int port) {
  //Le client se connecte au serveur, et créé un thread pour gérer la reception de messages.
  werase(view.chatWindow);
  wrefresh(view.chatWindow);
  this->socket = this->handshake(ip, port, pseudo, mdp); //connection au serveur
  pthread_t tid;
  pthread_create(&tid, nullptr, Client::manageInputs, this); //gestion des inputs
  this->manageSocketTraffic(); //gestion des messages entrants
  close(this->socket); //eccessible seulement quand le client se ferme
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
    view.fetchInput(*buffer); //renvoi le message de l'utilisateur dans le buffer
    buffer[strlen(buffer)] = '\0';
    message_t msg = {.timestamp = time(NULL), .message = string(buffer)};
    view.clearWindow(view.inputWindow); //redessiner la fenetre d'input quand le message est écrit
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
    if (msg.message.substr(0,1) == (string)"["){ //un message commencant par "[" est un message d'utilisateur
      mvwprintw(view.chatWindow, y+1, 1, msg.message.c_str());
      getyx(view.chatWindow, y, x);
      wrefresh(view.chatWindow);
    } else { //sinon c'est un plateau, 100% sûr
      mvwprintw(view.boardWindow, 0, 0, msg.message.c_str());
      wrefresh(view.boardWindow);
    }
  }
}

int Client::handshake(string ip, int port, string pseudo, string mdp) {
  int socket = checked(create_socket());
  if (connect_socket(socket, ip.c_str(), port) < 0) {
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
    fprintf(stderr, "Utilisation: ./client <port> [<style d'interface>] [<ip>]\n");
    exit(0);
  }
  const int port = atoi(argv[1]);
  if (port < 1024) {
    fprintf(stderr, "Le port doit être supérieur à 1023.\n");
    exit(0);
  }


//Ici style en argv 2, ip passe en argv 3, style Qt par défaut

  std::string ip;
  if (argc > 2) {
    ip = argv[2];
  }

  char pseudo[64];
  std::cout << "Entrez un pseudo" << std::endl;
  cin.getline(pseudo, 64);
  std::cout << "Entrez un mot de passe" << std::endl;
  char mdp[16];
  cin.getline(mdp, 16);
  Client client = Client(); //ici Client() prend un parametre style.
  client.runGame(pseudo, mdp, ip.c_str(), port);

  return 0;
}
