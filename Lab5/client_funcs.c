#include "client_funcs.h"

char *t1 = "xwrxwrxwr-------";
char *t2 = "----------------";
// end of stream 
const char EOS[] = "EOS";

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

// TODO: Keon's
int lcat(char filename[])
{
	
}

int lpwd()
{
	char cwd[128];

  getcwd(cwd, 128);

  printf("%s\n", cwd);
}
int lls(char pathname[])
{
  struct stat mystat, *sp;
  int k;
  char name[1024], cwd[128];

  if(pathname == NULL || strcmp(pathname, "") == 0)
  {
    getcwd(cwd, 128);
    strcpy(pathname, cwd);
  }

  sp = &mystat;
  if (k = lstat(pathname, sp) < 0){
     printf("no file found.\n");
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
  printf("LSing %s\n", file);
  struct stat fstat, *sp;
  int k, i;
  char ftime[64];

  sp = &fstat;
  if((k = lstat(file, &fstat)) < 0)
  {
    printf("ERROR: can't stat %s\n", file);
    return 0;
  }
  
  if ((sp->st_mode & 0xF000) == 0x8000)
    printf("-");
  if ((sp->st_mode & 0xF000) == 0x4000)
    printf("d");
  if ((sp->st_mode & 0xF000) == 0xA000)
    printf("l");

  for (i=8; i >= 0; i--){
    if (sp->st_mode & (1 << i))
      printf("%c", t1[i]);
    else
      printf("%c", t2[i]);
  }

  printf("%4d ",sp->st_nlink);
  printf("%4d ",sp->st_gid);
  printf("%4d ",sp->st_uid);
  printf("%8d ",sp->st_size);

  // print time
  strcpy(ftime, ctime(&sp->st_ctime));
  ftime[strlen(ftime)-1] = 0;
  printf("%s ",ftime);

  // print name
  printf("%s\n", file);
}

int ls_dir(char *file)
{
  DIR *d = opendir(file);
  struct dirent *dir;

  if(d == NULL) 
    printf("couldn't open the directory.\n");
  
  while((dir = readdir(d)) != NULL)
  {
    ls_file(dir->d_name);
  }
  closedir(d);
}
int lcd(char filename[])
{
	if(chdir(filename))
  {
    printf("changed cwd to %s", filename);
  }
}

// TODO: Keon's
int lmkdir(char filename[])
{
	
}

// TODO: Keon's
int lrmdir(char filename[])
{
	
}

int lrm(char filename[])
{
  if(unlink(filename) == 0)
  {
    printf("removed %s successfully!\n", filename);
  }
}

int readMessage(char *msg)
{
	// keep reading line from server until EOS is received
  n = read(sock, msg, MAX);
  while(strcmp(msg, EOS))
  {
    printf("%s", msg);
    n = read(sock, msg, MAX);
  }
}

int sendMessage(char msg[])
{
	// Send ENTIRE line to server
  n = write(sock, msg, MAX);
  printf("sent: %s\n", msg);
}