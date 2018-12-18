#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/resource.h>//rlimit的相关库，要不然会报未定义错误
 
#define OPEN_MAX_GUESS 256
 
 
long open_max(void)
{
   long openmax;
   struct rlimit rl;
   if((openmax = sysconf(_SC_OPEN_MAX)) < 0 || openmax == LONG_MAX)//_SC_OPEN_MAX:每个进程最大打开文件数
     {
		   if(getrlimit(RLIMIT_NOFILE,&rl) < 0)//获取每个进程最大打开文件描述符数
				  printf("1.can't get file limit ");
       if(rl.rlim_max == RLIM_INFINITY)
				  openmax = OPEN_MAX_GUESS;
       else
				openmax = rl.rlim_max;
						 
     }
		 printf("2.openmax == %ld \n",openmax);
}
int main()
{
  open_max();
  return 0;
}

