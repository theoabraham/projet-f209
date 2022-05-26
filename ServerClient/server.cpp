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
    //on attend les entrées des clients en boucle, sans jamais s'interrompre
    this->prepateFDSet(&read_set);
    int nactivities = checked(select(this->max_fd + 1, &read_set, nullptr, nullptr, nullptr));
    this->handleSocketReadActivity(&read_set, nactivities); //on gère les messages des clients
  }
}

void Server::forward(message_t* msg, vector<user_t*> receivers) {
  //envoie le message contenu dans msg a tous les clients contenus dans la liste des destinataires
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
  while (nactivities > 0 and i >= 0) { //pour chaque utilisateur, on analyse son message
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
        if((msg.message.substr(0,1) == (string)"/")){ //Si le message commence par "/" c'est une commande
          if (users[i]->activeGame != -1 && (int)games[users[i]->activeGame]->players.size() >= games[users[i]->activeGame]->neededPlayers){
            std::string command = msg.message.substr(msg.message.length() - 4, 4);
            std::cout<<command<<std::endl;
            this->handleMove(command, i); //donc on vérifie si c'est un coup
          }
          this->handleCommand(i, msg); //sinon c'est peut etre une commande, on sait pas
        } else {
          //Si c'est ni une commande ni une déconnexion alors c'est un message régulier
          //et il sera traité comme tel
          char date_buffer[32];
          struct tm* local_time = localtime(&msg.timestamp);
          strftime(date_buffer, sizeof(date_buffer), "%H:%M:%S", local_time); //on génère le marqueur temporel du message
          msg.message = "[" + string(date_buffer) + "] " + this->users[i]->name + ": " + msg.message;
          if (users[i]->activeGame != -1){ //si le joueur est en partie, il s'adresse aux autres joueurs
            this->forward(&msg, games[users[i]->activeGame]->players);
          } else {
            this->forward(&msg, users); //sinon il s'adresse aux joueurs dans leur totalité
          }
        }
      }
    }
    i--;
  }
}

void Server::handleCommand(int userIndex, message_t msg){
  //Cas dans lequel le message serait peut etre une commande
  if (msg.message.substr(1, 6) == "quit"){
    //ca m'a l'air assez auto-explicatif
    this->disconnectUser(userIndex);
  }
  if (msg.message.substr(1, 5) == "help"){
    //la encore c'est pas dur a comprendre
    message_t helpMessage;
    helpMessage.message = "[system] : " + games[users[userIndex]->activeGame]->game.inputFormat() + " (/leave pour quitter.)";
    ssend(users[userIndex]->socket, &helpMessage);
  }
  if (msg.message.substr(1, 5) == "play"){
    //commande pour commencer une partie
    if (users[userIndex]->activeGame == -1){
      shared_ptr<Board> tmpboard = shared_ptr<Board>(new DestruQtionBoard(2));
      shared_ptr<DisplayBoard> tmpdisplayBoard = shared_ptr<DisplayBoard>(new DisplayBoard(tmpboard));
      Game tmpgame = Game(tmpboard, tmpdisplayBoard);
      game_t *newGame = new game_t{ //création de la nouvelle partie
        .board = tmpboard,
        .displayBoard = tmpdisplayBoard,
        .game = tmpgame
      };
      newGame->players.push_back(users[userIndex]); //on ajoute l'utilisateur a sa partie
      this->games.push_back(newGame); //on ajoute la partie a l'index des parties du serveur
      users[userIndex]->activeGame = this->games.size() - 1; //on ajoute la partie au profil de l'utilisateur
      std::cout << users[userIndex]->activeGame << std::endl;
      message_t strBoard;
      strBoard.message = newGame->displayBoard->printBoard();
      ssend(users[userIndex]->socket, &strBoard); //on envoi son plateau a l'utilisateur
      }
  }
  if (msg.message.substr(1, 4) == "join"){
    //rejoindre une partie encore en cours
    if (users[userIndex]->activeGame == -1) { //si le joueur n'est pas deja dans une partie
      string toJoin = msg.message.substr(6, 2); //index de la partie a rejoindre
      game_t *game = games[atoi(toJoin.c_str())]; //la partie en question
      game->players.push_back(users[userIndex]);
      users[userIndex]->activeGame = atoi(toJoin.c_str());
      message_t strBoard;
      strBoard.message = game->displayBoard->printBoard();
      ssend(users[userIndex]->socket, &strBoard); //on envoie le plateau au joueur qui rejoint la partie
      if ((int)game->players.size() == game->neededPlayers){ //si le nombre de joueur requis est atteint
        message_t startGame;
        startGame.message = "[system] : C'est a " + game->players[game->activePlayer]->name + " de jouer!"; //on previens les joueurs d'a qui c'est le tour
        std::cout << startGame.message << std::endl;
        this->forward(&startGame, game->players);
      }
    }
  }
  if (msg.message.substr(1, 4) == "add") {
      string toAdd = msg.message.substr(5, ((int)msg.message.size() - 1));
      DB.askFriend(msg.message.substr(4, msg.message.size()));
  }
  if (msg.message.substr(1, 7) == "remove") {
      // le user perdant son amis à besoin d'etre connecté à la DB --> DB.connect(username)
      string toAdd = msg.message.substr(5, ((int)msg.message.size() - 1));
      DB.deleteFriendship(msg.message.substr(7, msg.message.size()));
  }
  //si la commande n'est pas implémentée, le message sera simplement ignoré
}

void Server::handleMove(string command, int userIndex){
  //gestion d'une commande (/Message) d'un utilisateur
  std::cout<<(int)this->users.size()<<std::endl;
  std::cout<<(int)this->games.size()<<std::endl;
  std::cout<<userIndex<<std::endl;
  std::cout<<this->users[userIndex]->activeGame<<std::endl;
  game_t *currentGame = this->games[this->users[userIndex]->activeGame];
  std::cout<<"test2"<<std::endl;
  if(currentGame->game.checkInput(command, currentGame->activePlayer)){
    std::cout<<"test3"<<std::endl;
    //Si le coup demandé est valide, on le joue et on affiche le nouveau plateau
    message_t strBoard;
    strBoard.message = currentGame->displayBoard->printBoard();
    this->forward(&strBoard, currentGame->players);
    std::cout<<"test4"<<std::endl;
    //Si la partie est finie : on affiche un message annoncant le joueur gagnant
    if (currentGame->board->isEnd()) {
      message_t endingMsg;
      endingMsg.message = "[system] : " + users[currentGame->activePlayer]->name + " remporte la victoire!";
      this->forward(&endingMsg, currentGame->players);
      std::cout<<"test5"<<std::endl;
    } else { //Sinon, on affiche un message qui annonce le début du tour du nouveau joueur actif.
      currentGame->activePlayer = (currentGame->activePlayer + 1) % currentGame->neededPlayers; //on passe au tour du prochain joueur
      message_t newTurnMsg;
      newTurnMsg.message = "[system] : C'est a " + currentGame->players[currentGame->activePlayer]->name + " de jouer!";
      this->forward(&newTurnMsg, currentGame->players);
      std::cout<<"test6"<<std::endl;
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
  char total[128];
  char username[64];
  char password[64];


  std::cout<<"Nouvelle connection"<<std::endl; 
  //On accepte la connection et on récupère le pseudo (envoyé depuis le client)
  int socket = accept_socket(this->master_socket, &remote_host);
  int nbytes = safe_read(socket, total, 128);
  if (nbytes <= 0) {
    return;
  }
  unsigned int pseudosize = total[0] - '0';
  std::cout << pseudosize << std::endl;

  for (unsigned int i=1;i<pseudosize+1;i++){
      username[i-1] = total[i];
  }
  username[pseudosize] = '\0';
  std::cout << username << std::endl;
  unsigned int pswsize = total[pseudosize+1] - '0';
  std::cout << pswsize << std::endl;

  for (unsigned int i=pseudosize+2; i < pseudosize+pswsize+2; i++){
      password[i-pseudosize-2] = total[i];
  }

  password[pswsize] = '\0';
  std::cout << password << std::endl;
  //username = (to_string(total).substr(1, pseudosize)).c_str();
  /* std::cout << username << " <- ici1 " << std::endl;
  int nbytes2 = safe_read(socket, password, 16);
  std::cout << password << " <- ici2 " << std::endl;
  if (nbytes2 <= 0) {
    return;
  }*/

  //std::cout << "Après saferead psw" << std::endl;
  //password[nbytes2] = '\0';
  bool checkusr = DB.isUserinDB(username);
  bool checkpsw = DB.checkPassword(username, password);
  const int ack = !( checkusr && checkpsw);
  cout << checkusr << " " << checkpsw << " " << ack << std::endl;
  nbytes = safe_write(socket, &ack, sizeof(int));
  if (nbytes <= 0) {
    return;
  }

  //DB.connect(username);
  //UI = DB.getUserInfo(); //met à jour les informations

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