#include "apue.h"

int main(void)
{
	struct stat statbuf;

	if(stat("foo",&statbuf) < 0)
		err_sys("stat error");

	if(chmod("foo",(statbuf.st_mode & ~S_IXGRP) | S_ISGID) <0)
		err_sys("chmod error for foo");

	if(chmod ("bar",S_IRUSR |S_IWUSR | S_IRGRP | S_IROTH) <0)
		err_sys ("chmod error for bar");

	exit(0);

	
}


/*
 amazingtai@AmazingTaideMacBook-Pro  ~/Desktop/OS/c/04_UNIX_folder   master  ls -l bar foo
----rw----  1 amazingtai  staff  0  9 19 19:56 bar
-rw-rw-rw-  1 amazingtai  staff  0  9 19 19:56 foo
 amazingtai@AmazingTaideMacBook-Pro  ~/Desktop/OS/c/04_UNIX_folder   master  ./a.out
 amazingtai@AmazingTaideMacBook-Pro  ~/Desktop/OS/c/04_UNIX_folder   master  ls -l bar foo
-rw-r--r--  1 amazingtai  staff  0  9 19 19:56 bar
-rw-rwSrw-  1 amazingtai  staff  0  9 19 19:56 foo
 amazingtai@AmazingTaideMacBook-Pro  ~/Desktop/OS/c/04_UNIX_folder   master 
 */