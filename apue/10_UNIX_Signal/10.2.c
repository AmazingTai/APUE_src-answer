#include "apue.h"
#include <signal.h>

int all_signo[] = {1, 2, 3, 4, 5, 6, 7, 8, 
9, 10, 11, 12 , 13, 14, 15, 17, 
18, 19, 20, 21, 22, 23, 24, 25, 
26, 27, 28, 29, 30, 31, 34, 35, 
36, 37, 38, 39, 40, 41, 42, 43, 
44, 45, 46, 47, 48, 49, 50, 51, 
52, 53, 54, 55, 56, 57, 58, 59, 
60, 61, 62, 63, 64};

char all_sigstr[61][20] = {"SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT", "SIGBUS", "SIGFPE",
"SIGKILL", "SIGUSR1", "SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM", "SIGCHLD",
"SIGCONT", "SIGSTOP", "SIGTSTP", "SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU", "SIGXFSZ",
"SIGVTALRM", "SIGPROF", "SIGWINCH", "SIGIO", "SIGPWR", "SIGSYS", "SIGRTMIN", "SIGRTMIN+1",
"SIGRTMIN+2", "SIGRTMIN+3", "SIGRTMIN+4", "SIGRTMIN+5", "SIGRTMIN+6", "SIGRTMIN+7", "SIGRTMIN+8", "SIGRTMIN+9",
"SIGRTMIN+10", "SIGRTMIN+11", "SIGRTMIN+12", "SIGRTMIN+13", "SIGRTMIN+14", "SIGRTMIN+15", "SIGRTMAX-14", "SIGRTMAX-13",
"SIGRTMAX-12", "SIGRTMAX-11", "SIGRTMAX-10", "SIGRTMAX-9", "SIGRTMAX-8", "SIGRTMAX-7", "SIGRTMAX-6", "SIGRTMAX-5",
"SIGRTMAX-4", "SIGRTMAX-3", "SIGRTMAX-2", "SIGRTMAX-1", "SIGRTMAX"};

typedef struct sigstr{
	int signo;
	char *str;
	struct sigstr *next;
}SIGSTR;

void init(SIGSTR *st){
	st = (SIGSTR *)malloc(sizeof(SIGSTR));
	st->next = NULL;
	st->signo = -1;
	st->str = "init";
}

void insert(SIGSTR *st, int signo, char *str, int i)
{
	SIGSTR *tst = st;
	if (i == 0)
		tst->next = NULL;
	while(tst->next != NULL)
	{
		tst = tst->next;
	}
	SIGSTR *newstr = (SIGSTR *)malloc(sizeof(SIGSTR));
	newstr->signo = signo;
	newstr->str = str;
	newstr->next = NULL;
	printf("%d : %s\t%s\n", newstr->signo, newstr->str, str);


	if(tst->next == NULL)
	{
		tst->next = newstr;
	}

}

void get_sig_str(SIGSTR *p_st){

	int i, j;
	for ( i = 0; i < 61; i++){
		insert(p_st, all_signo[i], all_sigstr[i], i);
	}
}

int sig2str(int signo, char str[])
{
    SIGSTR st, *tst;
	int flag = 0;
    init(&st);
   	get_sig_str(&st);
    tst = st.next;
    while(tst)
    {
        if(signo==tst->signo){
			flag = 1;
            break;}
        tst = tst->next;
    }
	if (flag) {
    	strcpy(str, tst->str);
		return 0;
	}else
		return 1;

}

int str2sig(const char *str,int *signop)
{
    SIGSTR st,*tst;
	int flag = 0;
    init(&st);
    get_sig_str(&st);
    tst = st.next;
    while(tst)
    {
        if(strcmp(str,tst->str) == 0){
			flag = 1;
            break;}
        tst = tst->next;
    }
	if(flag) {
    	*signop = tst->signo;
		return 0;
	}else
		return 1;
}

void main(void)
{
	char str[30], str1[30];
	int signo = 0;
	int signo1 = 0;
	
	printf("input the signo:");
	scanf("%d", &signo);
	if (signo < 1 || signo > 64 ){
		printf("input the signo error\n");
		return;
	}
	int ret = sig2str(signo, str);
	printf("----------------------------------\n");
	if (ret == 0)
		printf("signo :%d\tstr : %s\n", signo, str);
	else
		printf("can't find the signo %d\n", signo);
	
	printf("input the SIGNALL:");
	scanf("%s", str);	
	ret = str2sig(str,&signo);
	printf("----------------------------------\n");
	if (ret == 0)
		printf("signo :%d\tstr : %s\n", signo, str);
	else
		printf("can't find the signal %s\n", str);

}
