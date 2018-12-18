#include <stdio.h>
#include <sys/stat.h>

void my_setbuf(FILE *fp, char *restrict buf)
{
    if (buf == NULL) 
    {                                           /* no buffer */
        setvbuf(fp, buf, _IONBF, 0);
    }
    else 
    {
        int fd;
        struct stat fp_stat;

        fstat(fileno(fp), &fp_stat);
        if (S_ISCHR(fp_stat.st_mode)) 
        {                                       /* line buffer */
            setvbuf(fp, buf, _IOLBF, BUFSIZ);
        }
        else {                                  /* full buffer */
            setvbuf(fp, buf, _IOFBF, BUFSIZ);
        }
    }
}

