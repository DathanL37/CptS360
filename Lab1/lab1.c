#include <stdio.h>
#include <stdlib.h>

#define DEC_BASE 10
#define OCT_BASE 8
#define HEX_BASE 16

typedef unsigned int u32;

int *ip;
char *table = "0123456789ABCDEF";

int myprintf(char *str, ...)
{
  char *cp = str;
  int i = 0, k = 0;

  // point ip to cpu.ebp
  asm("movl %ebp, ip");

  // Point at parameters
  ip += 3;
  
  // Go through formatted string
  for(i; cp[i] != '\0'; i++)
  {
    switch(cp[i])
    {
      case '\n':
        putchar(cp[i]); putchar('\r');
      break;
      
      case '\%':
        switch(cp[++i])
        {
          case 'c':
            putchar(*ip);
          break;

          case 's':
            printstr(*ip);
          break;

          case 'u':
            printu(*ip);
          break;

          case 'd':
            printd(*ip);
          break;

          case 'o':
            printo(*ip);
          break;

          case 'x':
            printx(*ip);
          break;
        }
        // Advance ip to next argument in stack
        ip++;
      break;
      
      default:
        putchar(cp[i]);
      break;
    }
  }
}

int mymain(int argc, char *argv[], char *env[])
{
  int i;

  myprintf("in mymain(): argc=%d\n", argc);

  for (i=0; i < argc; i++)
      myprintf("argv[%d] = %s\n", i, argv[i]);
  
  // WRITE CODE TO PRINT THE env strings
  i = 0;
  while(env[i]){
    myprintf("env[%d] = %s\n", i, env[i]);
    i++;
  }

  myprintf("---------- testing YOUR myprintf() ---------\n");
  myprintf("this is a test\n");
  myprintf("testing a=%d b=%x c=%c s=%s\n", 123, 123, 'a', "testing");
  myprintf("string=%s, a=%d  b=%u  c=%o  d=%x\n",
           "testing string", -1024, 1024, 1024, 1024);
  myprintf("mymain() return to main() in assembly\n"); 
}

int printstr(char *s)
{
  int i = 0;
  for(i; s[i] != '\0'; i++)
  {
    putchar(s[i]);
  }
}

int printu(u32 x)
{
  if (x==0)
     putchar('0');
  else
     printNum(x, DEC_BASE);
}

int printd(int x)
{
  int sign, sizeInt, i = 0;
  sizeInt = ((sizeof(int) * 8) - 1);

  if(0 == x) {
    putchar('0'); 
    return 0; 
  }

  // Check sign bit
  sign = x;
  sign = sign >> sizeInt;
  sign &= 1;
  // Negative check
  
  if(sign) 
  {
// TODO: Fix floating point error exception. 
    putchar('-'); 
    
    // Flip bits and add 1
    x = ~x;
    x++;
  }

  // Print rest of integer  
  printNum(x, DEC_BASE);
}

void printNum(u32 x, int base)
{
  char c;

  if (x != 0)
  {
     c = table[x % base];
     printNum(x / base, base);
     putchar(c);
  }
}

int printo(u32 x)
{
  printNum(x, OCT_BASE);
}

int printx(u32 x)
{
  putchar('0'); 
  putchar('x');
  printNum(x, HEX_BASE);
}
