#include "apue.h"

#define BUFFSIZE 4096
int main(void)
{
	int 	n;
	char  	buf[BUFFSIZE];

	while(n = read(STDIN_FILENO,buf,BUFFSIZE) > 0)
		if(write(STDIN_FILENO,buf,10) != n )
			err_sys("write error");

	if(n < 0)
		err_sys("read error");
	exit(0);
	
}
//创建一个空洞文件，空洞文件是多线程的支持点之一，因为空洞文件的存在才能支持多线程断点续传