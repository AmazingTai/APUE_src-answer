# include "apue.h"
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int 	val;
	if(argc != 2)
		err_sys("usage:a.out<descriptor#>");

	if((val = fcntl(atoi(argv[1]),F_GETFL,0)) <0 )
		err_sys("fcntl error for fd %s",atoi(argv[1]));

	switch (val & O_ACCMODE)
	{
		case O_RDONLY:
			printf("read only");
			break;
		case O_WRONLY:
			printf("write only");
			break;
		case O_RDWR:
			printf("read write");
			break;
		default :
		err_dump("unknow access mode");

	}
	if(val & O_APPEND)
		printf(",append");
	if(val & O_NONBLOCK)
		printf(",nonblocking");
	if(val & O_SYNC)
		printf(",synchronous writes");

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
	if(val & O_FSYNC)
		printf(",synchronous writes");
#endif
	
	putchar('\n');
	exit(0);

}

/*
$ ./a.out 1 > temp.foo  就是输出重定向，temp.foo是个新建的文件，那么fcntl(1, F_GETFL, 0);就是判断temp.foo的读写属性，新建的temp.foo默认是read write的

$ ./a.out 0 > temp.foo同理，输出被重定向到temp.foo，但是判断的仍然是标准输入，也就是终端，故还是read write

//下面讨论./a.out 2 2>>temp.foo

先来补点理论知识

2代表stderr

2>>filename
        # 重定向并追加stderr到文件"filename". 
那么./a.out 2 2>>temp.foo 就是检查被重定向后的文件temp.foo的在文件描述符2上的属性


对于

$ ./a.out 5 5<>temp.foo同样需要补理论知识

[j]<>filename
        # 为了读写"filename", 把文件"filename"打开, 并且将文件描述符"j"分配给它. 
        # 如果文件"filename"不存在, 那么就创建它. 
        # 如果文件描述符"j"没指定, 那默认是fd 0, stdin. 
5<>temp.foo表示在文件描述符5上打开文件temp.foo以供读和写，程序就是检查temp.foo的读写属性，很明显我是"<>"的，也就是读写打开这个文件的
那么结果也就是read write
*/