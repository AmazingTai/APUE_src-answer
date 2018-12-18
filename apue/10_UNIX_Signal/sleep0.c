#include "apue.h"
#include <signal.h>
#include <unistd.h>

static void sig_alrm(int signo)
{
	//nothing ,return to wake up the pause
}
unsigned int sleep1(unsigned int seconds)
{
	if(signal(SIGALRM,sig_alrm) == SIG_ERR){
		err_sys("signal error");
		return (seconds);
	}
	alarm(seconds);
	pause();
	return (alarm(0));

}
