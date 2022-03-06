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
        mvwprintw(chatWindow, 4, 1, "Wrong input, please enter C, D or Q.");
        wrefresh(chatWindow);
        this->fetchInput(*gameMode);
        this->gameMode[strlen(gameMode)]='\0';
      }
    }
  }
}

void Client::displayMenu(std::vector<const char*> options){
  clearWindow(chatWindow);
  int y = 0;
  for(const char* option: options){
    y++;
    mvwprintw(chatWindow, y, 1, option);
  }
  wrefresh(chatWindow);
}

void Client::clearWindow(WINDOW * window) {
  werase(window);
  box(window, 0, 0);
  wrefresh(window);
}

void Client::loginRoutine() {
    //Print dans la fenetre chatwindow en position y=1, x=1,
    clearWindow(chatWindow);
    mvwprintw(chatWindow, ++line_counter, 1,"Entrez un pseudo pour vous connecter: ");
    wrefresh(chatWindow);
    this->fetchInput(*pseudo);
    this->pseudo[strlen(pseudo)]='\0';

    // si fichier comporte caractère invalide
    if (!DatabaseHandler::isStringValid(pseudo)){
        mvwprintw(chatWindow, ++line_counter, 1,"Le pseudo entré comporte un caractère interdi.");
        wrefresh(chatWindow);
        exit(0);
    }
    // si fichier existe pas
    if (!DatabaseHandler::does_file_exist(pseudo)){
        char answer;
        while (!(answer=='Y' or answer=='y' or answer=='N' or answer=='n')) {
            mvwprintw(chatWindow, ++line_counter, 1, "Fichier inexistant. Voulez vous creer un compte? (Y/n) :");
            wrefresh(chatWindow);
            this->fetchInput(answer);
        }
        if (answer=='y' or answer=='Y'){
            //deux mdp
            char Password[80];char checkPassword[80];

            //premier mdp
            mvwprintw(chatWindow, ++line_counter, 1, "Entrez un mot de passe (attention il est visible de tous) :");
            wrefresh(chatWindow);
            this->fetchInput(*Password);
            Password[strlen(Password)] = '\0';

            //confirmation
            mvwprintw(chatWindow, ++line_counter, 1, "Confirmez votre mot de passe :");
            wrefresh(chatWindow);
            this->fetchInput(*checkPassword);
            checkPassword[strlen(checkPassword)] = '\0';

            //si deux psw egaux
            if(!strcmp(Password, checkPassword)){
                DatabaseHandler::createFile(pseudo, Password);
            }
        }
    }
}

void Client::connectRoutine(DatabaseHandler *dbh) {
    mvwprintw(chatWindow, ++line_counter, 1, "Utilisateur trouvé.");
    wrefresh(chatWindow);

    char Password[80];
    mvwprintw(chatWindow, ++line_counter, 1, "Entrez votre mot de passe:");
    wrefresh(chatWindow);
    this->fetchInput(*Password);
    Password[strlen(Password)] = '\0';
    // vérifie le password
    while (!dbh->checkPswd(Password)) {
      mvwprintw(chatWindow, ++line_counter, 1, "Mot de passe invalide. Réessayez");
      wrefresh(chatWindow);
      this->fetchInput(*Password);
      Password[strlen(Password)] = '\0';
    }
    // liste d'amis
    std::vector<std::string> toaddVect= dbh->getToAddFriendList();
    mvwprintw(chatWindow, ++line_counter, 1, "Voulez vous ajouter ces amis ?(Y/other)");
    wrefresh(chatWindow);
    char answer[80];
    if (toaddVect.size()) { // si le vecteur est non vide
        for (auto s: toaddVect) {
            mvwprintw(chatWindow, ++line_counter, 1, s.c_str());
            wrefresh(chatWindow);
            this->fetchInput(*answer);
            answer[strlen(answer)] = '\0';
            if (!strcmp(answer, "Y")) {
                mvwprintw(chatWindow, ++line_counter, 1, "Amis ajouté");
                wrefresh(chatWindow);
                dbh->tempVectadd(s);
            }
        }
    }
    dbh->writeFriends();
    // ajout d'amis
    char friend_pseudo[80];
    while (strcmp(friend_pseudo, "n")){
        mvwprintw(chatWindow, ++line_counter, 1, "Entrez un ami à ajouter (n pour annuler):");
        wrefresh(chatWindow);
        this->fetchInput(*friend_pseudo);
        friend_pseudo[strlen(friend_pseudo)] = '\0';
        if (strcmp(friend_pseudo, "n") and !DatabaseHandler::does_file_exist(friend_pseudo)){
            mvwprintw(chatWindow, ++line_counter, 1, "Ami innexistant.");
            wrefresh(chatWindow);
        }else if(strcmp(friend_pseudo, "n")){
            dbh->writeFriendstoAdd(friend_pseudo);
            mvwprintw(chatWindow, ++line_counter, 1, "Demande d'amis envoyée.");
            wrefresh(chatWindow);
        }
    }
}

void Client::runGame(string pseudo, string ip, int port) {
  //Le client se connecte au serveur, et créé un thread pour gérer la reception de messages.
  werase(chatWindow);
  box(chatWindow, 0, 0);
  wrefresh(chatWindow);
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