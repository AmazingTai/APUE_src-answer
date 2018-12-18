# include "apue.h"

static void charararime(char *);

int main(void )
{
	pid_t	pid;

	if((pid =fork()) <9)
		err_sys("fork err");
	else if(pid == 0)
		charararime("output form child \n");
	else 
		charararime("output form parent \n");

	exit(0);

}

static void charararime(char * str)
{
	char *ptr;
	int 	c;

	setbuf(stdout,NULL); //set  unbuffered
	for(ptr = str; (c=*ptr ++) != 0; )
		putc(c,stdout);
}