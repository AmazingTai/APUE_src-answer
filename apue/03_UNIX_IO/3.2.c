# include "apue.h"
#include <fcntl.h>


#define MAXN 4096
#define EXIT_SUCC 0
#define EXIT_FALL -1

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;//OPEN_MAX每个进程最大打开文件数，linux为1024
#else
static long openmax = 0;
#endif

int my_dup2(int fd1,int fd2)
{
	int stack[MAXN];
	int i=0;
	int n=0;
	int top=0;

	if(fd1 == fd2)
		return fd2;
	if((fd1 > openmax) || fd2 <0 )
	{
		printf("invalid fd2\n");
		return EXIT_FALL;
	}
	while((n = dup(fd1)) <fd2 )
	{
		if( n == -1)
		{
			printf("system cannot make filedes\n");
			return EXIT_FALL;
		}
		stack[top++] = n;

	}
	close(fd2);

	if(dup(fd1) == -1)
	{
		printf("dup function error\n");
		return EXIT_FALL;
	}

	for(i=0;i<top;i++)
		close(stack[i]);

	return fd2;

}

int main(int argc,char *argv[])
{
	int fd1,fd2;

	if(argc != 3)
	{
		printf("Parameter error\n");
		return EXIT_FALL;
	}

	//fd1 = open(argv[1],O_RDWR);
	fd1= open(argv[1], O_RDWR);
	if(fd1 == -1)
	{
		printf("system cannot open %s\n",argv[1]);
		return EXIT_FALL;
	}

	fd2 = atoi(argv[2]);
	if(my_dup2(fd1,fd2) != EXIT_FALL)
	{
		write(fd2,"amazing",sizeof("amazing"));

	}

	return 0;


}