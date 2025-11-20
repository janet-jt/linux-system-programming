#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void){
	pid_t pid;
	int status;
	printf("My PID is %d\n", getpid());
	
	if( (pid = fork()) == -1 ){
		perror("Can't fork");
		return 1;
	}
	if(pid == 0){
		sleep(10);
		printf("Hello and goodbye from the child!\n");
		exit(0);
	}else if(pid > 0){
		printf("Hello from the parent process! My child had PID %d\n", pid);
		waitpid(pid, &status, 0);
		sleep(120);
	}else{
		fprintf(stderr, "Something went wrong forking\n");
		return 1;
	}
	return 0;
}

