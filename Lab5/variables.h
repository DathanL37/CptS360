#ifndef VARIABLES_H
#define VARIABLES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdarg.h>

#define  MAX 256
#define STAT_MAX 10000
typedef struct {
    char *name;
    char *value;
} ENTRY;
ENTRY entry[STAT_MAX];

struct stat mystat, *sp;

// Define variables:
struct sockaddr_in  server_addr, client_addr, name_addr;
struct hostent *hp;

int  sock, newsock;                  // socket descriptors
int  serverPort;                     // server port number
int  r, length, n;                   // help variables

int sendMessage(const char *message, ...);
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
int processCommand(char command[]);

#endif