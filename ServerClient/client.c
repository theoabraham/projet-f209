/*
Code par
Emile Merian 000518697
Théo Abraham 000515744
*/
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include "common.h"

void* recevoir(void *socketptr) {
  int sock = *((int*) socketptr);
  ssize_t nbytes = 1;
  while (1) {
    char *recvbuffer;
    nbytes = receive(sock, (void *)&recvbuffer);
    if (nbytes > 0) {
      printf("%s \n\n", recvbuffer);
    }else if (nbytes == 0) {
      printf("Le serveur a été éteint, fermeture des clients...");
      errExit("Client eteint");
    }
  }
  return 0;
}

int main(int argc, char const *argv[]) {

  if (argc != 4){
    printf("Fonctionnement : ./client <pseudo> <IP> <port>\n");
    return 1;
  }

  const char *pseudo = argv[1];

  const char *IP = argv[2];

  int port = atoi(argv[3]);

  int sock = checked(socket(AF_INET, SOCK_STREAM, 0));
  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port); //8080

  // Conversion de string vers IPv4 ou IPv6 en binaire
  checked(inet_pton(AF_INET, IP, &serv_addr.sin_addr)); //"127.0.0.1"

  checked(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)));
  ssend(sock, (void*) pseudo, sizeof(pseudo));
  char buffer[1024];
  ssize_t nbytes = 1;
  pthread_t thread;
  pthread_create(&thread, NULL, recevoir, &sock);
  while (nbytes > 0 && fgets(buffer, 1024, stdin)) {
    printf("\033[A\33[2KT\r");
    char message[1024];
    time_t timestamp = time(NULL);
    char *dt = ctime(&timestamp);
    strcat(message, "\n");
    strcat(message, dt);
    strcat(message, buffer);
    size_t len = strlen(message);
    message[len - 1] = '\0';
    nbytes = ssend(sock, message, len);
    bzero(message, len);
  }
  return 0;
}