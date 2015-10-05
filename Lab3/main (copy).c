#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int pid, status, pd[2], ARGC = 0;

char line[128], command[64];
char *PATH[128];
char HOME[128];
char CWD[128];
char USER[32];
char *ARGV[64], **ENV;

int main(int argc, char *argv[ ], char *env[])
{
  env = ENV;
  getHome();
  getPath();
  getUsername();


  while(1)
  {
    input();
    execute();
    resetArgv();
  }
}

int getHome()
{
  char *home = getenv("HOME");
  char *token = strtok(home, ":");
  strcpy(HOME, token);
}

int getPath()
{
  // Grab PATH environment variable
  char *path = getenv("PATH");
  // Get each path with : as delim
  char *token = strtok(path, ":");
  int i = 0;
  while(token != NULL)
  {
    PATH[i] = token;
    i++;
    token = strtok(NULL, ":");
  }
}

int getUsername()
{
  char *user = getenv("LOGNAME");
  char *token = strtok(user, ":");
  strcpy(USER, token);
}

int resetArgv()
{
  // reset argv
  int i = 0;
  while(ARGV[i])
  {
    //memset(ARGV[i], 0, 64);
    ARGV[i] = NULL;
    i++;
  }
  ARGC = 0;
}


int input()
{
  // prompt
  printf("%s@%s > ", USER, CWD);
  gets(line);

  // get command
  char *token = strtok(line, " ");
  strcpy(command, token);
  ARGV[0] = malloc(sizeof(char)*64);
  strcpy(ARGV[0], token);
  ARGC++;

  // get other arguments
  int i = 1, concatenating = 0;
  token = strtok(NULL, " ");
  while(token != NULL)
  {
    printf("token: %s\nlength: %d\n", token, strlen(token));
    
    if(concatenating == 0){
      ARGV[i] = malloc(sizeof(char)*64);
      strcat(ARGV[i], token);
      ARGC++;
    }
    // concatenating string
    if (token[0] == '\'' || token[0] == '\"')
    { 
      strcat(ARGV[i], " ");
      concatenating = 1;
      --i;
      if (token[strlen(token)-1] == '\'' || token[strlen(token)-1] == '\"')
      {// base case: single word
        ARGV[i][strlen(ARGV)-1] = 0;
        concatenating = 0;
      }
    }
    else if (token[strlen(token)-1] == '\'' || token[strlen(token)-1] == '\"')
    { // case: end of string
      // don't add duplicates
      if (strcmp(ARGV[i], token))
      {
        strcat(ARGV[i], token);
        printf("done concatenating\n%s\n", ARGV[i]);
        // get rid of quotes
        int k = 0, len = strlen(ARGV[i]);
        for (k; k < len; k++)
        {
          ARGV[i][k] = ARGV[i][k+1];
        }
        ARGV[i][len-2] = 0;
      }
      concatenating = 0; 
    }
    else if (concatenating)
    {// case: middle words
      // don't add duplicates

       printf("concatenating\n");

       strcat(ARGV[i], " ");
       strcat(ARGV[i], token);
       printf("argv %s\n", ARGV[i]);
      --i;
    }
    i++;
    token = strtok(NULL, " ");
  }
}

int execute()
{
  if(strcmp(command, "cd") == 0)
  {
    // get destination of cd command
    if(ARGV[1] != NULL && chdir(ARGV[1]) == 0)
    {
      strcpy(CWD, ARGV[1]);
    }
    else if(ARGV[1] == NULL || strcmp(ARGV[1], "") == 0) 
    {
      chdir(HOME); 
      strcpy(CWD, HOME);
    }
    else perror("directory not found\n");
  }
  else if(strcmp(command, "exit") == 0){ exit(1); }
  else
  {
    forkAChild();
  }
}

int forkAChild()
{
  int z = 0;
  printf("argc = %d\n", ARGC);
  

  // used to get sub args from ARGV for each command and pipe
  char *argv[64];
  pid = fork();

  if (pid < 0){   // fork() may fail. e.g. no more PROC in Kernel
    perror("fork failed");
    exit(1);
  }
  if (pid)
  { // PARENT EXECUTES THIS PART 
    printf("THIS IS %d  MY PARENT=%d\n", getpid(), getppid());
  
    pid = wait(&status);
    printf("DEAD CHILD=%d, HOW=%04x\n", pid, status);
  } 
  else
  { // child executes this part
    printf("I am    %d  my parent=%d\n", getpid(), getppid());

    int i = 0;
    for (i; ARGV[i] != NULL; i++)
    {
      // redirect
      if(strcmp(ARGV[i], ">") == 0 || 
        strcmp(ARGV[i], "<") == 0 ||
        strcmp(ARGV[i], ">>") == 0)
      {
        redirect(ARGV[i], ARGV[i+1]);
        break;
      }
      // pipe
      else if(strcmp(ARGV[i], "|") == 0)
      {
        pipe(pd); // create pipe
        int lpid = fork(); // fork child

        if (lpid) // child
        {
          // copy first half of args to local argv

          int j = 0;
          for (j; j < i; j++)
          {
            printf("b4exec argv[%d] = %s\n", j, ARGV[j]);
            argv[j] = ARGV[j];
          }
          argv[j] = NULL;

          close(pd[0]);
          dup2(pd[1], 1);
          close(pd[1]);
          exec(argv);
        }
        else // parent
        {
          char *second[64];
          // copy other half of ARGV for execution
          int start = 0;
          for (++i; ARGV[i] != NULL; i++)
          {
            // copy to front of array
            second[start] = ARGV[i];
            start++;
          }
          printf("out of loop\n");

          z = 0;
          while(second[z])
          {
            printf("sec[%d] %s\n", z, second[z]);
            z++;
          }

          close(pd[1]);
          dup2(pd[0], 0);
          close(pd[0]);
          exec(second);
        }
        break;
      }
    }
    
    i = 0;
    while(ARGV[i])
    {
      printf("1copying %s\n", ARGV[i]);
      argv[i] = ARGV[i];
      i++;
    }

    exec(argv);
  }
}

int exec(char *argv[])
{
  int z = 0;
  while(argv[z])
  {
    printf("exec argv[%d] = %s\n", z, argv[z]);
    z++;
  }
  //Check each bin folder for command by concatenating pathname with input[0]
  int i = 0;
  char temp[1024];
  // check each path in PATH variable
  while(PATH[i] != NULL) 
  {
      // construct new path
      strcpy(temp, PATH[i]);
      strcat(temp, "/");
      strcat(temp, command);
      printf("temp: %s\n", temp);
      // this will execute command if it's found
      execve(temp, argv, ENV);
      i++;
  }
}

int redirect(char direction[], char filename[])
{
  printf("direction: %s\nfilename: %s\n", direction, filename);
  if (strcmp(direction, "<") == 0)
  {
    return createIn(filename);
  }
  else if(strcmp(direction, ">") == 0)
  {
    return createOut(filename);
  }
  else if(strcmp(direction, ">>") == 0)
  {
    return createApp(filename);
  }
  return 1;
}

int createApp(char *file)
{
  // close file descriptor 1
  close(1);
  return open(file, O_WRONLY|O_APPEND, 0644);
}

int createOut(char *file)
{
  // close file descriptor 1
  close(1);
  return open(file, O_WRONLY|O_CREAT, 0644);
}

int createIn(char *file)
{
  // close file descriptor 0
  close(0);
  return open(file, O_RDONLY);
}

int scan(char *head, char *tail)
{
  int i = 0, r = -1;
  for(i; i < strlen(line); i++)
  {
    if('|' == line[i])
    {
      // Update this when doing multiple pipes
      strncpy(head, line, i);
      memcpy(tail, line+i, strlen(line));
      r = 0;
    }
  }
  printf("head: %s\ntail: %s\n", head, tail);
  return r;
}