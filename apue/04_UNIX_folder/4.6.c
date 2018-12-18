# include "apue.h"
#include <fcntl.h>

int main(int argc, char * argv[])
{
	if(argc != 3)
		err_sys("error");
	int fd1,fd2;
	if(fd1 = open(argv[1],O_RDONLY) < 0)
		err_sys("open error");

	if(fd2 = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC) < 0)
		err_sys("open error");

	char *buf;
	while(read(fd1,buf,1))
	{
		printf("%s\n", &buf);
		if((buf!=NULL) && (*buf!='\0'))
		{
			if(write(fd2,buf,1) < 0)
				err_sys("write error");

		}
	}
	close(fd1);
	close(fd2);

	exit(0);

}