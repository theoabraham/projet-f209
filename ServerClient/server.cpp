#include "server.h"
#include "../Quorridor/Controller/Game.hpp"
#include "../Quorridor/Model/Board.hpp"
#include "../Quorridor/View/DisplayBoard.hpp"

#include <string.h>
#include <sys/select.h>
#include <unistd.h>

#include <ctime>
#include <iostream>
#include <string>

#include "socketlib.h"

Server::Server() {}

void Server::run(int port) {
  //lance a proprement parler le serveur
  this->master_socket = checked(create_socket());
  bind_socket(this->master_socket, port);
  listen_socket(this->master_socket);
  this->max_fd = master_socket;

  fd_set read_set;
  while (true) {
    this->prepateFDSet(&read_set);
    int nactivities = checked(select(this->max_fd + 1, &read_set, nullptr, nullptr, nullptr));
    this->handleSocketReadActivity(&read_set, nactivities);
  }
}

void Server::forward(message_t* msg, vector<user_t*> receivers) {
  //envoie le message contenu dans msg a tous les clients connectés
  for (unsigned i = 0; i < receivers.size(); i++) {
    user_t* u = receivers[i];
    if (ssend(u->socket, msg) <= 0) {
      this->disconnectUser(i);
    }
  }
}

void Server::prepateFDSet(fd_set* read_set) {
  //Prépare les connections (sockets) avec tous les clients
  FD_ZERO(read_set);
  FD_SET(this->master_socket, read_set);
  for (unsigned i = 0; i < this->users.size(); i++) {
    user_t* user = this->users[i];
    FD_SET(user->socket, read_set);
  }
}

void Server::handleSocketReadActivity(fd_set* in_set, int& nactivities) {
  //Réaction quand un client envoi un message
  if (nactivities <= 0) return;
  if (FD_ISSET(this->master_socket, in_set)) {
    //nouvelle connection
    this->handleNewConnection();
    nactivities--;
  }
  unsigned i = this->users.size() - 1;
  while (nactivities > 0 and i >= 0) {
    int socket = this->users[i]->socket;
    message_t msg;
    if (FD_ISSET(socket, in_set)) {
      nactivities--;
      size_t nbytes = receive(socket, &msg);
      if (nbytes < 0) {
        exit(1);
      } else if (nbytes == 0) {
        //si le "message" est vide, déconnection
        this->disconnectUser(i);
      } else {
        // message_buffer[nbytes] = '\0';
        bool enoughPlayers = ((int)this->games[users[i]->activeGame]->players.size() - 1 >= this->games[users[i]->activeGame]->neededPlayers);
        //Si le message commence par un point ET provient du joueur actif ET que la partie est en cour :
        if((msg.message.substr(0,1) == (string)"/")){
          if (enoughPlayers){ //faudra changer avec game_t
            std::string command = msg.message.substr(msg.message.length() - 4, 4);
            //Si le coup demandé est valide, on le joue et on affiche le plateau
            this->handleMove(command, socket);
          }
          if (msg.message.substr(1, 6) == "leave"){
            this->disconnectUser(i);
          }
          if (msg.message.substr(1, 5) == "help"){
            message_t helpMessage;
            helpMessage.message = "[system] : " + this->game.inputFormat() + " (/leave pour quitter.)";
            ssend(users[i]->socket, &helpMessage);
          }
          if (msg.message.substr(1, 5) == "play"){
            game_t *newGame = new game_t{
              board = shared_ptr<Board>(new DestruQtionBoard(2)),
              displayBoard = shared_ptr<DisplayBoard>(new DisplayBoard(board)),
              game = Game(board, displayBoard)
            };
            newGame->players.push_back(users[i]);
            this->games.push_back(newGame);
            users[i]->activeGame = this->games.size() - 1;
            message_t strBoard;
            strBoard.message = this->displayBoard->printBoard();
            this->forward(&strBoard, games[users[i]->activeGame]->players);
          }
          if (msg.message.substr(1, 4) == "join"){
            string toJoin = msg.message.substr(6, 2);
            this->games[atoi(toJoin.c_str())]->players.push_back(users[i]);
            users[i]->activeGame = atoi(toJoin.c_str());
            message_t strBoard;
            strBoard.message = this->displayBoard->printBoard();
            this->forward(&strBoard, games[users[i]->activeGame]->players);
          }
        } else {
          //Si de base ce n'était pas une commande (ou que ce n'était pas le tour du joueur expediteur)
          //C'est un message, qui est renvoyé a tout le monde
          char date_buffer[32];
          struct tm* local_time = localtime(&msg.timestamp);
          strftime(date_buffer, sizeof(date_buffer), "%H:%M:%S", local_time);
          msg.message = "[" + string(date_buffer) + "] " + this->users[i]->name + ": " + msg.message;
          if (users[i]->activeGame != -1){
            this->forward(&msg, games[users[i]->activeGame]->players);
          } else {
            this->forward(&msg, users);
          }
        }
      }
    }
    i--;
  }
}

void Server::handleMove(string command, int clientSocket){
  //gestion d'une commande (/Message) d'un utilisateur
  game_t *currentGame = this->games[users[clientSocket]->activeGame];
  if(clientSocket == currentGame->players[currentGame->activePlayer]->socket && this->game.checkInput(command, currentGame->activePlayer)){
    message_t strBoard;
    strBoard.message = this->displayBoard->printBoard();
    this->forward(&strBoard, currentGame->players);
    //Si la partie est finie : on affiche un message annoncant le joueur gagnant
    if (this->board->isEnd()) {
      message_t endingMsg;
      endingMsg.message = "[system] : " + users[currentGame->activePlayer]->name + " remporte la victoire!";
      this->forward(&endingMsg, currentGame->players);
    } else { //Sinon, on affiche un message qui annonce le début du tour du nouveau joueur actif.
      currentGame->activePlayer = (currentGame->activePlayer + 1) % currentGame->neededPlayers;
      message_t newTurnMsg;
      newTurnMsg.message = "[system] : C'est a " + currentGame->players[currentGame->activePlayer]->name + " de jouer!";
      this->forward(&newTurnMsg, currentGame->players);
    }
  }
}

void Server::disconnectUser(unsigned user_num) {
  //Gestion de la déconnection d'un utilisateur
  user_t* user = this->users[user_num];
  game_t* game = games[user->activeGame];
  this->users.erase(this->users.begin() + user_num);
  this->max_fd = this->master_socket;
  for (auto user : this->users) {
    if (user->socket > this->max_fd) {
      this->max_fd = user->socket;
    }
  }
  if(user->activeGame != -1) {
    for (int i = 0; i < (int)game->players.size(); i++) {
      if (game->players[i] == user) {
        game->players[i] = game->players[game->players.size() - 1];
        game->players.pop_back();
      }
    }
  }
  //Si le nombre de joueurs restant est inssufisant pour jouer, la partie se met en pause dans
  //handleSocketReadActivity() mais les joueurs sont prévenus ici
  /*
  if (this->registeredPlayers < this->neededPlayers){
    message_t waitNewPlayerMsg;
    waitNewPlayerMsg.message = "[system] : Plus assez de joueurs connectés pour continuer la partie, partie mise en pause";
    this->forward(&waitNewPlayerMsg, game->players);
  }
  */
}

void Server::handleNewConnection() {
  //Gestion d'une nouvelle connection
  struct sockaddr remote_host;
  char username[64];
  char password[16];

  //On accepte la connection et on récupère le pseudo (envoyé depuis le client)
  int socket = accept_socket(this->master_socket, &remote_host);
  int nbytes = safe_read(socket, username, 64);
  if (nbytes <= 0) {
    return;
  }
  username[nbytes] = '\0';
  int nbytes2 = safe_read(socket, password, 16);
  if (nbytes2 <= 0) {
    return;
  }
  password[nbytes2] = '\0';
  const int ack = !(DB.isUserinDB(username) && DB.checkPassword(username, password));
  std::cout << ack << std::endl;
  nbytes = safe_write(socket, &ack, sizeof(int));
  if (nbytes <= 0) {
    return;
  }
  DB.connect(username);

  //On créé un "profil" de user contenant pseudo, port et version
  user_t* new_user = new user_t;
  new_user->socket = socket;
  new_user->version = 0;
  new_user->name = username;
  this->users.push_back(new_user);
  char* ip;
  uint16_t port;
  to_ip_host(&remote_host, &ip, &port);
  //On envoit le plateau actuel au nouvel arrivant
  if (socket > this->max_fd) {
    this->max_fd = socket;
  }
}

int main(int argc, char const* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Utilisation: ./server <port>\n");
    exit(0);
  }
  const int port = atoi(argv[1]);
  if (port < 1024) {
    fprintf(stderr, "Le port doit être supérieur à 1023.\n");
    exit(0);
  }
  Server server = Server();
  server.run(port);
  return 0;
}