#include "apue.h"
int main(void)
{
    int     c;
    while(c = getc(stdin) != EOF)
      if(putc(c,stdout) == EOF)
       err_sys("output error");

      if(ferror(stdin))
        err_sys("inout error");

     exit(0);    
}