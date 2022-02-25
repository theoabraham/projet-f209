/*
Code par
Emile Merian 000518697
Théo Abraham 000515744
*/
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //strlen
#include <sys/socket.h>
#include <sys/time.h>  //FD_SET, FD_ISSET, FD_ZERO macros
#include <unistd.h>    //close
#include <time.h>
#include <signal.h>

#include "common.h"

int nclients = 0; //nombre de clients
int clients[1024]; //liste des clients

static void sigintHandler(int sig) { //tiré de Delftstack
    for (int i = 0; i < nclients; i++) {
      ssend(clients[i], NULL, 0);
      close(clients[i]);
    }
    errExit("Fermeture"); //voir errExit dans common.h
  }

int main(int argc, char *argv[]) {

  if (argc != 2){
    printf("Fonctionnement : ./server <port>");
    return 1;
  }

  int port = atoi(argv[1]);

  struct timeval tv = {1, 0};
  int opt = 1;
  int master_socket = checked(socket(AF_INET, SOCK_STREAM, 0));
  checked(setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)));

  // type of socket created
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port); //8080
  checked(bind(master_socket, (struct sockaddr *)&address, sizeof(address)));
  checked(listen(master_socket, 3));

  size_t addrlen = sizeof(address);
  fd_set readfds;
  int clients[1024];
  char *pseudo[1024];

  signal(SIGINT, sigintHandler); //Gestion du CTRL+C

  while (1) {

    FD_ZERO(&readfds);
    FD_SET(master_socket, &readfds);
    int max_fd = master_socket;
    for (int i = 0; i < nclients; i++) {
      FD_SET(clients[i], &readfds);
      if (clients[i] > max_fd) {
        max_fd = clients[i];
      }
    }
    tv = (struct timeval){1,0};
    
    // wait for an activity on one of the sockets, timeout is 0.5
    select(max_fd + 1, &readfds, NULL, NULL, &tv);
    
    time_t timestamp = time(NULL);
    char *dt = ctime(&timestamp);

    if (FD_ISSET(master_socket, &readfds)) {
      // Si c'est le master socket qui a des donnees, c'est une nouvele connexion.
      clients[nclients] = accept(master_socket, (struct sockaddr *)&address, (socklen_t *)&addrlen);
      receive(clients[nclients], (void*) &pseudo[nclients]);
      strcat(pseudo[nclients], "\0");
      char welcomeMessage[1024] = ""; //conception du message de bienvenue
      strcat(welcomeMessage, dt);
      strcat(welcomeMessage, "Bienvenue : "); 
      strcat(welcomeMessage, pseudo[nclients]);
      strcat(welcomeMessage, "\0");
      nclients++;
      for (int i = 0; i < nclients; i++) {
        ssend(clients[i], welcomeMessage , sizeof(welcomeMessage));
      }
      bzero(welcomeMessage, strlen(welcomeMessage));
    } else {
      // Sinon, c'est un message d'un client
      for (int i = 0; i < nclients; i++) {
        if (FD_ISSET(clients[i], &readfds)) {
          char *buffer;
          size_t nbytes = receive(clients[i], (void *)&buffer);
          strcat(buffer, "\0");
          char message[1024]; //conception du message
          strcat(message, "Received from : ");
          strcat(message, pseudo[i]);
          strcat(message, "\n");
          strcat(message, buffer);
          if (nbytes > 0) {  // closed
            for (int j = 0; j < nclients; j++) {
              ssend(clients[j], message, sizeof(message));
            }
          bzero(message, strlen(message));
          bzero(buffer, strlen(buffer));
          } else {
            close(clients[i]);
            // On deplace le dernier socket a la place de libre pour ne pas faire de trou.
            clients[i] = clients[nclients - 1];
            pseudo[i] = pseudo[nclients - 1];
            nclients--;
          }
        }
      }
    }
  }
  return 0;
}