#include "variables.h"

char *t1 = "xwrxwrxwr-------";
char *t2 = "----------------";
// end of stream 
const char EOS[] = "EOS";

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
  if((token = strtok(NULL, " ")) != NULL)
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
    myPwd();
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

int sendMessage(const char *line, ...)
{
  char message[MAX];
  va_list args;
  // init args with number of arguments
  va_start(args, line);
  vsprintf(message, line, args);

  // send the echo line to client 
  n = write(newsock, message, MAX);
  printf("sent: %s\n", message);

  va_end(args);
}

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
  char cwd[128];
  getcwd(cwd, 128);

  sendMessage("%s\n", cwd);
  sendMessage(EOS);
}

int myLs(char *pathname)
{
  struct stat mystat, *sp;
  int k;
  char name[1024], cwd[1024];

  sp = &mystat;
  if (k = lstat(pathname, sp) < 0){
     sendMessage("no file found.\n");
     return 0;
  }
  strcpy(name, pathname);

  if (S_ISDIR(sp->st_mode))
      ls_dir(name);
  else
      ls_file(name);
}

int ls_file(char *file)
{
  struct stat fstat, *sp;
  int k, i;
  char ftime[64], message[MAX];

  sp = &fstat;
  if((k = lstat(file, &fstat)) < 0)
  {
    sendMessage("ERROR: can't stat file.\n");
    return 0;
  }
  
  if ((sp->st_mode & 0xF000) == 0x8000)
    message[0] = '-';
  if ((sp->st_mode & 0xF000) == 0x4000)
    message[0] = 'd';
  if ((sp->st_mode & 0xF000) == 0xA000)
    message[0] = 'l';

  for (i=8; i >= 0; i--){
    if (sp->st_mode & (1 << i))
      message[9-i] = t1[i];
    else
      message[9-i] = t2[i];
  }

  printf("%4d ",sp->st_nlink);
  printf("%4d ",sp->st_gid);
  printf("%4d ",sp->st_uid);
  printf("%8d ",sp->st_size);

  // print time
  strcpy(ftime, ctime(&sp->st_ctime));
  ftime[strlen(ftime)-1] = 0;
  printf("%s  ",ftime);

  // print name
  printf("%s", file);
  printf("</p>"); 
}

int ls_dir(char *file)
{
  DIR *d = opendir(file);
  struct dirent *dir;

  if(d == NULL) 
    sendMessage("couldn't open the directory.\n");
  
  while((dir = readdir(d)) != NULL)
  {
    ls_file(dir->d_name);
  }
  closedir(d);

}

int myCd(char *pathname)
{
  sendMessage("CDing to %s\n", pathname);
  sendMessage(EOS);
}

// TODO: Keon's
int myMkdir(char *pathname)
{
  if(mkdir(pathname, 777) == 0)
  {
    sendMessage("created successfully!");
    sendMessage("");
  }
  sendMessage("%s", EOS);
  return 0;
}

// TODO: Keon's
int myRmdir(char *pathname)
{
  if(rmdir(pathname) == 0)
  {
    sendMessage("removed dir successfully!");
    sendMessage("");
  }
  sendMessage("%s",EOS);
}

int myRm(char *pathname)
{
  if(unlink(pathname) == 0)
  {
    sendMessage("removed file successfully!");
    sendMessage("");
  }
}

// TODO: Keon's
int myGet(char *pathname)
{
  FILE *file = fopen(pathname,"r");
  char *buffer = (char*)malloc(sizeof(char)*MAX);
  
  if(file == 0)
    return 0;
  while(fread(buffer, 1, MAX, file) >= MAX)
    {
      sendMessage("%s", buffer);
    }
  sendMessage("%s", EOS);
  return 0;
}

int sendMesage(const char *line, ...)
{
  char message[MAX];
  va_list args;

  va_start(args,line);

  n=write(sock,message,MAX);
  printf("sent: %s\n", message);

  va_end(args);
}
