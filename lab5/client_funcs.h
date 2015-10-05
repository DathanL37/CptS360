#ifndef CLIENT_FUNCS_H
#define CLIENT_FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netdb.h>

#define MAX 256

// Define variables
struct hostent *hp;              
struct sockaddr_in  server_addr; 

int sock, r, n;
int SERVER_IP, SERVER_PORT; 

int clientInit(char *argv[]);
int lcat(char filename[]);
int lpwd(char filename[]);
int lls(char filename[]);
int lcd(char filename[]);
int lmkdir(char filename[]);
int lrmdir(char filename[]);
int lrm(char filename[]);
int readMessage(char *msg);
int sendMessage(char msg[]);

#endif