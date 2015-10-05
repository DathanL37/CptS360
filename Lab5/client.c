//**************************** ECHO CLIENT CODE **************************
// The echo client client.c

#include "client_funcs.h"

// clinet initialization code


main(int argc, char *argv[ ])
{
  char line[MAX], ans[MAX];

  if (argc < 3){
     printf("Usage : client ServerName SeverPort\n");
     exit(1);
  }

  clientInit(argv);

  printf("********  processing loop  *********\n");
  while (1){
    printf("input a line : ");
    bzero(line, MAX);                // zero out line[ ]
    fgets(line, MAX, stdin);         // get a line (end with \n) from stdin

    line[strlen(line)-1] = 0;        // kill \n at end
    if (line[0]==0)                  // exit if NULL line
       exit(0);

    /*
    readMessage(line);
    
    do magic here

    sendMessage(line);
     */
  }
}


