#define _POSTIX_C_SOURCE 200809L
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

//Reference: https://www.cnblogs.com/52php/p/5813867.html

void sigHandler(int sig);

int main(void){
	pid_t pid;
	pid = getpid();
	struct sigaction action;
	sigset_t set;
	
	printf("Program running with PID %d\n", pid);
	action.sa_handler = sigHandler;
	sigfillset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	
	sigemptyset(&set);
	sigaddset(&set, SIGINT);

	sigprocmask(SIG_BLOCK, &set, NULL);
	
	for(;;){
		sleep(10);
	}
	sigprocmask(SIG_UNBLOCK, &set, NULL);


	return 0;
}

void sigHandler(int sig){
	if(sig == SIGUSR1){
		printf("received USR1 signal\n");
	}else if(sig == SIGUSR2){
		printf("received USR2 signal\n");
	}
}
