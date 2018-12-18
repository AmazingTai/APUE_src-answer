#include <stdio.h>                                                                                                                                   
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
 
#ifdef OPEN_MAX
static long openmax = OPEN_MAX;//OPEN_MAX每个进程最大打开文件数，linux为1024
#else
static long openmax = 0;
#endif
 
/* If OPEN_MAX is indeterminate ,no gurante this is adequate */
#define OPEN_MAX_GUESS 256
 
long open_max(void)
{
	//其实if内的程序没有执行因为已经定义了OPEN_MAX，
           if(openmax == 0)
		{
			errno = 0;
			if((openmax = sysconf(_SC_OPEN_MAX)) < 0)//_SC_OPEN_MAX:每个进程最大打开文件数
			 {
				printf("1.openmax= %ld\n",openmax);
				if(errno == 0)
					openmax = OPEN_MAX_GUESS; /*it's indeterminate*/
				else
					printf("sysconf error for _SC_OPEN_MAX");
			 }	
		}
	printf("2.openmax= %ld\n",openmax);
  return(openmax);
}
int main()
{
  open_max();
  return 0;
}//编译 
 

 /*
 AmazingTaideMacBook-Pro:c amazingtai$ ./a.out
 2.openmax= 10240
*/

