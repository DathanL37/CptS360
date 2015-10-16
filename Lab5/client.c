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
  char command[64], path[64];
  sscanf(line, "%s %s", command, path);

  if (strcmp(command, "lls") == 0)
  {
    lls(path);
  }
  else if (strcmp(command, "lmkdir") == 0)
  {
    lmkdir(path);
  }
  else if (strcmp(command, "lrmdir") == 0)
  {
    lrmdir(path);
  }
  else if (strcmp(command, "lrm") == 0)
  {
    lrm(path);
  }
  else if (strcmp(command, "lpwd") == 0)
  {
    lpwd();
  }
  else if (strcmp(command, "lcat") == 0)
  {
    lcat(path);
  }
  else if (strcmp(command, "lcd") == 0)
  {
    lcd(path);
  }
  else if (strcmp(command, "put") == 0)
  {
    myPut(path);
  }
  else if (strcmp(command, "get") == 0)
  {
    myGet(path);
  }
  else
  { // server command
    sendMessage("%s", line);
    readMessage(line);
  }
}

