/*
 * Name: Thom Hemenway & Keon Sadatian
 * Date: 10/5/15
 * Lab 5 
 */
#include "variables.h"

main(int argc, char *argv[])
{
  char *hostname;
  char line[MAX];

  if (argc < 2)
    hostname = "localhost";
  else
    hostname = argv[1];
 
  serverInit(hostname); 

  // Try to accept a client request
  while(1)
  {
    printf("server: accepting new connection ....\n"); 
     // Try to accept a client connection as descriptor newsock
    length = sizeof(client_addr);
    newsock = accept(sock, (struct sockaddr *)&client_addr, &length);
    if (newsock < 0)
    {
      printf("server: accept error\n");
      exit(1);
    }
    printf("server: accepted a client connection from\n");
    printf("-----------------------------------------------\n");
    printf("        IP=%d  port=%d\n", inet_ntoa(client_addr.sin_addr.s_addr), ntohs(client_addr.sin_port));
    printf("-----------------------------------------------\n");
    
    readMessage(line);
  }
}