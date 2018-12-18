#include "apue.h"
int     globvar = 6;                /*  external variable in initialized data  */
#define     SIZE    256
int
main(void)
{
    int     var;                    /*  automatic variable on the stack  */
    pid_t   pid;
    int     i;
    char    buf[SIZE];

    var = 88;

    printf("before vfork\n");           /*  we don't flush stdio  */
    if ((pid = vfork()) < 0)
        err_sys("vfork error");
    else if(pid == 0)
    {
        globvar++;                      /*  child  */
        var++;                          /*  modify parent's variables  */
        fclose(stdout);
        exit(0);

    }
    /*  parent continue here  */
    i = printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,
            var);
    sprintf(buf, "%d\n", i);
    write(STDOUT_FILENO, buf, strlen(buf));
    exit(0);

}
