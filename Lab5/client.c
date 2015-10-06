/*
 * Name: Thom Hemenway & Keon Sadatian
 * Date: 10/5/15
 * Lab 5 
 */
#include "client_funcs.h"

main(int argc, char *argv[ ])
{
  char line[MAX], ans[MAX];

  if (argc < 3){
     printf("Usage : client ServerName SeverPort\n");
     exit(1);
  }

  clientInit(argv);

  printf("********  processing loop  *********\n");
  while (1)
  {
    printf("input a line : ");
    bzero(line, MAX);                // zero out line[ ]
    fgets(line, MAX, stdin);         // get a line (end with \n) from stdin

    line[strlen(line)-1] = 0;        // kill \n at end
    if (line[0]==0)                  // exit if NULL line
      exit(0);

    processCommand(line);
  }
}

int processCommand(char line[])
{
  char copy[128];
  strcpy(copy, line);
  char *t = strtok(copy, " ");
  char cmd[64];
  strcpy(cmd, t);

  if (line[0] == 'l' && strcmp(cmd, "ls"))
  { // local command
    char *token = strtok(line, " ");
    char  command[64], path[64];

    // get command and path from line
    strcpy(command, token);
    token = strtok(NULL, " ");
    strcpy(path, token);
  }
  else
  { // server command
    sendMessage(line);
    readMessage(line);
  }
}

