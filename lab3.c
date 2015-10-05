#include "lab3.h"

void main(int argc, char *argv[], char *env[])
{
  int i = 0;
  for(i = 0; i < argc; i++)
    printf("argv[%d]: %s\n", i, argv[i]);
  i = 0;
  while(env[i])
    {
      printf("env[%d]: %s\n",i, env[i]);
      i++;
    }
  mysh(argc,argv,env);
}

void mysh(int argc, char *argv[], char *env[])
{
  char line[128], *cmds[64];
  int i = 0, j = 0;

  printf("Welcome to MySH\n");
  while(strcmp(cmds[1],"quit"))
    {
      printf("Enter command: \n");
      //      scanf("%128s",line);
      fgets(line, 128, stdin);
      printf("Command Entered: \"%s\"\n",line);
      tokenLine(line, cmds);
      shell(argc, argv, env, cmds);      
      printf("Press Key to Continue\n");
      fflush(stdin);
      printf("Current stdin: \"%s\"\n",*stdin);
      fgetc(stdin);
    }
  printf("broke out of loop\n");
}

void tokenLine(char *str, char *tokens[])
{
  int i, j=0, arguments = 0;
  char temp[128], line[64][128];
  arguments = strWordCount(str);

  printf("tokenLine() running...\n");
  strTokenizer(str);
  for(i=0;j<arguments;i++)
    {
      //printf("Copying string \"%s\"\n",(str + i));
      //strcpy(temp,(str + i));
      //printf("\"%s\" copied to temp holder\n",(str + i));

      printf("Attempting to copy \"%s\"\n",(str + i));
      mystrcpy(line[j],(str + i));
      printf("\"%s\" copied to line[%d]\n",(str + i),j);
      strcpy(temp,"'\0'");
      //strcpy(tokens[j],(str+i));
      printf("String Copy Successful!\n");
      i+=strlen(line[j]);
      j++;
    }
  printf("Attempting to print to tokens\n");
  for(i = 0;i<j;i++)
    {
      tokens[i] = line[i];
    }
  return;
}

int strWordCount(char *str)
{
  int i, count = 0;
  for(i=0;str[i];i++)
    {
      if(isspace(str[i]))
	 count++;
    }
      return count;
}

void strTokenizer(char *str)
{
  int i = 0;
  for(;str[i];i++)
    {
      if(isspace(str[i])) //checks for space in string, and replaces it with a null character
	str[i] = '\0';
    }
  return;
}

void mystrcpy(char destination[], char *source)
{
  int i;
  printf("mystrcpy() running...\n");
  for(i=0;source[i];i++)
    {
      printf("destination[%d] : \"%c\" = source[%d] : \"%c\"\n",i,destination[i],i,source[i]);
      destination[i] = source[i];
    }
  destination[i] = '\0';
  return;
}
