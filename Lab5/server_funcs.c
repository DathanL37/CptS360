#include "variables.h"

int readMessage(char *line)
{
	while(1)
	{
    n = read(newsock, line, MAX);
    if (n==0)
    {
      printf("server: client died, server loops\n");
      close(newsock);
      break;
    }

    printf("client said: %s\n", line);

    //process command && respond
    processCommand(line);
  }
}

int processCommand(char command[])
{
  char *token = strtok(command, " ");
  char cmd[64], path[64];
  int r = 0, com = 0;

  strcpy(cmd, token);
  token = strtok(NULL, " ");
  strcpy(path, token);

  // figure out which command to run
  if (strcmp(cmd, "mkdir") == 0)
  {
    myMkdir(path);
  }
  else if (strcmp(cmd, "rmdir") == 0)
  {
    myRmdir(path);
  }
  else if (strcmp(cmd, "get") == 0)
  {
    myGet(path);
  }
  else if (strcmp(cmd, "put") == 0)
  {
    myPut(path);
  }
  else if (strcmp(cmd, "pwd") == 0)
  {
    myPwd(path);
  }
  else if (strcmp(cmd, "ls") == 0)
  {
    myLs(path);
  }
  else if (strcmp(cmd, "cd") == 0)
  {
    myCd(path);
  }
  else if (strcmp(cmd, "rm") == 0)
  {
    myRm(path);
  }
  else
  {
    sendMessage("invalid command.");
  }
}

int sendMessage(char command[])
{
  // send the echo line to client 
  printf("sent: %s\n", command);
  n = write(newsock, command, MAX);
}

// Server initialization code:

int serverInit(char *name)
{
   printf("==================== server init ======================\n");   
   // get DOT name and IP address of this host

   printf("1 : get and show server host info\n");
   hp = gethostbyname(name);
   if (hp == 0){
      printf("unknown host\n");
      exit(1);
   }

   printf("    hostname=%s  IP=%d\n",
               hp->h_name,  inet_ntoa(*(long *)hp->h_addr));
  
   //  create a TCP socket by socket() syscall
   printf("2 : create a socket\n");
   sock = socket(AF_INET, SOCK_STREAM, 0);
   if (sock < 0){
      printf("socket call failed\n");
      exit(2);
   }

   printf("3 : fill server_addr with host IP and PORT# info\n");
   // initialize the server_addr structure
   server_addr.sin_family = AF_INET;                  // for TCP/IP
   server_addr.sin_addr.s_addr = htonl(INADDR_ANY);   // THIS HOST IP address  
   server_addr.sin_port = 0;   // let kernel assign port

   printf("4 : bind socket to host info\n");
   // bind syscall: bind the socket to server_addr info
   r = bind(sock,(struct sockaddr *)&server_addr, sizeof(server_addr));
   if (r < 0){
       printf("bind failed\n");
       exit(3);
   }

   printf("5 : find out Kernel assigned PORT# and show it\n");
   // find out socket port number (assigned by kernel)
   length = sizeof(name_addr);
   r = getsockname(sock, (struct sockaddr *)&name_addr, &length);
   if (r < 0){
      printf("get socketname error\n");
      exit(4);
   }

   // show port number
   serverPort = ntohs(name_addr.sin_port);   // convert to host ushort
   printf("    Port=%d\n", serverPort);

   // listen at port with a max. queue of 5 (waiting clients) 
   printf("5 : server is listening ....\n");
   listen(sock, 5);
   printf("===================== init done =======================\n");
}

int myPwd()
{

}

int myLs(char *pathname)
{

}

int myCd(char *pathname)
{

}

int myMkdir(char *pathname)
{

}

int myRmdir(char *pathname)
{

}

int myRm(char *pathname)
{

}

int myGet(char *pathname)
{

}

int myPut(char *pathname)
{

}