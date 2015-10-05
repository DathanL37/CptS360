#ifndef VARIABLES_H
#define VARIABLES_H
#include <stdio.h>
#include <stdlib.h>

#define  MAX 256

// Define variables:
struct sockaddr_in  server_addr, client_addr, name_addr;
struct hostent *hp;

int  sock, newsock;                  // socket descriptors
int  serverPort;                     // server port number
int  r, length, n;                   // help variables

int sendMessage(char message[]);
int serverInit(char *name);
int readMessage(char *line);
int myPwd();
int myLs(char *pathname);
int myCd(char *pathname);
int myMkdir(char *pathname);
int myRmdir(char *pathname);
int myRm(char *pathname);
int myGet(char *pathname);
int myPut(char *pathname);

#endif