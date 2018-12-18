#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <fcntl.h>  
#include <errno.h>  

#define BUFFSIZE 4096  

int main(int argc, char* argv[])  
{  
    if (argc != 2)  
    {  
        printf("Please enter the file name!/n");  
        exit(1);  
    }  

    int fd;  

    if ((fd = open(argv[1],O_RDWR | O_APPEND))== -1)  
    {  
        printf("%s",strerror(errno));  
        exit(2);  
    }  

    off_t offset = 10;  

    if (lseek(fd,offset,SEEK_CUR) == -1)  
    {  
        printf("cannot seek./n");  
    }  
    else  
    {  
        printf("seek OK!");  
    }  

    int n;  
    char buf[BUFFSIZE];  

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)  
    {  
        if (write(fd, buf, n) != n)  
        {  
            printf("write error!/n");  
            exit(3);  
        }  
    }  

    if (n < 0)  
    {  
        printf("read error!/n");  
        exit(4);  
    }  

    exit(0);  
}  


///Users/amazingtai/Desktop/1.txt