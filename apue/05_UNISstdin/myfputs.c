#include "apue.h"
int main(void)
{
    char    buf[MAXLINE];
    while(fgetc(buf,MAXLINE,stdin) != NULL)
      if(fputc(buf,stdout) == EOF)
       err_sys("output error");

      if(ferror(stdin))
        err_sys("inout error");

     exit(0);    
}