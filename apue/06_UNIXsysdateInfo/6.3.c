#include <sys/utsname.h>
#include "apue.h"

int main(void)
{
	struct utsname *ptr;
	int tmp;

	ptr = (struct utsname *)malloc(sizeof(struct utsname)); //sizeof

	if((tmp = uname(ptr)) < 0)
		err_sys("uname error");


	printf(" %s\n %s\n %s\n %s\n %s\n", ptr->sysname, ptr->nodename, ptr->release,
           ptr->version, ptr->machine);

	exit(0);
}