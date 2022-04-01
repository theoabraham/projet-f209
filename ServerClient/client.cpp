#include "client.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "socketlib.h"


void *Client::manageInputs(void *instance) {
  //Version void* de manage input pour pouvoir creer le thread
  Client *c = (Client *)instance;
  c->manageInputs();
  return nullptr;
}

void ClientNC::manageInputs() {
  // Le client peut ecrire et envoyer ses messages
  char buffer[1024];
  while (true) {
    view->fetchInput(*buffer); //renvoi le message de l'utilisateur dans le buffer
    buffer[strlen(buffer)] = '\0';
    message_t msg = {.timestamp = time(NULL), .message = string(buffer)};
    view->clearWindow(view->inputWindow); //redessiner la fenetre d'input quand le message est écrit
    if (ssend(this->socket, &msg) <0) {
      exit(0);
    }
  }
  close(this->socket);
  exit(0);
}

void ClientNC::manageSocketTraffic() {
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
      mvwprintw(view->chatWindow, y+1, 1, msg.message.c_str());
      getyx(view->chatWindow, y, x);
      wrefresh(view->chatWindow);
    } else { //sinon c'est un plateau, 100% sûr
      mvwprintw(view->boardWindow, 0, 0, msg.message.c_str());
      wrefresh(view->boardWindow);
    }
  }
}

int Client::handshake(string ip, int port, string pseudo, string mdp) {
  int socket = checked(create_socket());
  unsigned int pseudosize= pseudo.size();
  unsigned int mdpsize = mdp.size();
  string final = to_string(pseudosize) + pseudo + to_string(mdpsize) + mdp;
  if (connect_socket(socket, ip.c_str(), port) < 0) {
    exit(1);
  }
  // Send username
  if (safe_write(socket, final.c_str(), final.length()) <= 0){
      exit(1);
  }

  /*
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
  */

  return socket;
}


void ClientNC::runMenu(string pseudo, string mdp, string ip, int port){
  keypad(view->inputWindow, TRUE);
  bool _ = true;
  while(_){
    char menuChoice;
    view->displayMenu({"Option :", "(P)lay", "Chose (N)umber of players", "Chose (G)amemode"}); //options de base
    view->fetchInput(menuChoice); //demande un choix a l'utilisateur
    if (menuChoice == 'P'){ //les choix prennent la forme de lettres majuscules.
      _ = false;
    }
    if (menuChoice == 'N') {
      view->displayMenu({"(2) joueurs", "(4) joueurs", "Certains modes ne permettent que 4 joueurs"}); //options de nombre de joueurs
      view->fetchInput(*numberPlayers);
      while (strcmp(numberPlayers, "2") != 0 && strcmp(numberPlayers, "4") != 0) { //tant que la réponse n'est pas correcte : 
        view->clearWindow(view->chatBoxWindow);
        mvwprintw(view->chatWindow, 3, 0, "Wrong input, please enter 2 or 4.");
        wrefresh(view->chatWindow);
        view->fetchInput(*numberPlayers);
      }
      this->numberPlayers[strlen(numberPlayers)]='\0';
    }
    if (menuChoice == 'G'){
      view->displayMenu({"(C)lassic", "(D)estruQtion", "(Q)QQuorridor"}); //options de mode de jeu
      view->fetchInput(*gameMode);
      while (strcmp(gameMode, "C") != 0 && strcmp(gameMode, "D") != 0 && strcmp(gameMode, "Q") != 0) { //tant que la réponse n'est pas correcte : 
        view->clearWindow(view->chatBoxWindow);
        mvwprintw(view->chatWindow, 3, 0, "Wrong input, please enter C, D or Q.");
        wrefresh(view->chatWindow);
        view->fetchInput(*gameMode);
      }
      this->gameMode[strlen(gameMode)]='\0';
    }
  }
  this->runGame(pseudo, mdp, ip, port); //normalement, lance le jeu, mais la ca bug si on le lance d'ici...
}

void ClientNC::runGame(string pseudo, string mdp, string ip, int port) {
  //Le client se connecte au serveur, et créé un thread pour gérer la reception de messages.
  werase(view->chatWindow);
  wrefresh(view->chatWindow);
  this->socket = this->handshake(ip, port, pseudo, mdp); //connection au serveur
  pthread_t tid;
  pthread_create(&tid, nullptr, Client::manageInputs, this); //gestion des inputs
  this->manageSocketTraffic(); //gestion des messages entrants
  close(this->socket); //eccessible seulement quand le client se ferme
}


void ClientGUI::manageSocketTraffic(){
  while (true) {
    message_t msg;
    size_t nbytes = receive(this->socket, &msg);
    if (nbytes <= 0) {
      exit(0);
    }
    if (msg.message.substr(0,1) == (string)"["){ //un message commencant par "[" est un message d'utilisateur
      //Envoie le message dans le chatroom
    }
    else{
      //envoie le plateau transformer en matrice a boardGUI
    }
    std::cout<<msg.message<<std::endl; 
  }
}

/*
void build_mat_from_str(const std::string& str){


    unsigned int i=0;unsigned int j=0;
    for (unsigned char c:str) {
        int int_c = (int) c;
        if (49 <= int_c && int_c <= 57){// ord('0')=48 et ord('9')=59 -> on cherche juste les entier entre 1 et 9
            j+= (int_c-48);             // par exemple '3' --> ord('3')=51 --> 51-48 = 3
            std::cout << "Positionné à la case:" << i << ',' << j << std::endl;
        }else if (c=='/'){
            i+=1;                       //saute une ligne
            j=0;                        //repart à la colone 0
            std::cout << "Départ à la case:" << i << ',' << j << std::endl;
        }else if(c=='P'){
            // appelle le constructeur piece{char} -> implique avoir un constructeur qui prend un char en paramètre
            std::cout << "Construction de la piece "<< c << " en:" << i << ',' << j << std::endl;
            j+=1;                       //passe a la case suivante une fois la piece ajoutée
        }else if (c=='V'){
            //mur vertical
            ???
        }else{
            // mur horizontale 'H', appelle le constructeur de mur vertical
            std::cout << "Construction du mur horizontal "<< H << " en:" << i << ',' << j << std::endl;
            j+= LONGUEUR DU MUR; // je suppose 2
        }
    }
}
*/ 


int main(int argc, char *argv[]) {
  if (argc < 4) {
    fprintf(stderr, "Utilisation: ./quoridor <port> [<ip>] [<style d'interface> (I or T)] \n");
    exit(0);
  }
  const int port = atoi(argv[1]);
  if (port < 1024) {
    fprintf(stderr, "Le port doit être supérieur à 1023.\n");
    exit(0);
  }

  std::string ip;
  ip = argv[2];

  std::string view; 
  view = argv[3]; 
  if (view=="T"){
    char pseudo[64];
    std::cout << "Entrez un pseudo: " << std::endl;
    cin.getline(pseudo, 64);
    std::cout << "Entrez un mot de passe: " << std::endl;
    char mdp[16];
    cin.getline(mdp, 16);
    ClientNC client = ClientNC(); //ici Client() prend un parametre style.
    client.runGame(pseudo, mdp, ip.c_str(), port);
    return 0;
  }
  else if (view=="I"){
    QApplication app(argc,argv);
    
    ClientGUI * client = new ClientGUI();
    client->getMenu(); 
    //MenuWindow window;
    //window.show();
    return app.exec();
  }    
  else{
    fprintf(stderr, "Utilisation: ./quoridor <port> [<ip>] [<style d'interface> (I(nterface) or T(erminal))] \n ");
  }
}
