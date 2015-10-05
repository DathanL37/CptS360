#include "client_funcs.h"

int clientInit(char *argv[])
{
  printf("======= clinet init ==========\n");

  printf("1 : get server info\n");
  hp = gethostbyname(argv[1]);
  if (hp==0){
     printf("unknown host %s\n", argv[1]);
     exit(1);
  }

  SERVER_IP   = *(long *)hp->h_addr;
  SERVER_PORT = atoi(argv[2]);

  printf("2 : create a TCP socket\n");
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock<0){
     printf("socket call failed\n");
     exit(2);
  }

  printf("3 : fill server_addr with server's IP and PORT#\n");
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = SERVER_IP;
  server_addr.sin_port = htons(SERVER_PORT);

  // Connect to server
  printf("4 : connecting to server ....\n");
  r = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (r < 0){
     printf("connect failed\n");
     exit(1);
  }

  printf("5 : connected OK to \007\n"); 
  printf("---------------------------------------------------------\n");
  printf("hostname=%s  IP=%d  PORT=%d\n", 
          hp->h_name, inet_ntoa(SERVER_IP), SERVER_PORT);
  printf("---------------------------------------------------------\n");

  printf("========= init done ==========\n");
}

int lcat(char filename[])
{
	
}
int lpwd(char filename[])
{
	
}
int lls(char filename[])
{
	
}
int lcd(char filename[])
{
	
}
int lmkdir(char filename[])
{
	
}
int lrmdir(char filename[])
{
	
}
int lrm(char filename[])
{
	
}

int readMessage(char *msg)
{
	// Send ENTIRE line to server
  n = write(sock, msg, MAX);
  printf("sent: %s\n", msg);
}

int sendMessage(char msg[])
{
	// Send ENTIRE line to server
  n = write(sock, msg, MAX);
  printf("sent: %s\n", msg);
}