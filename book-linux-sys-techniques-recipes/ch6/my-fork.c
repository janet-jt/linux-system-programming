#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main(void){
	pid_t pid;
	int status;

	printf("My PID is %d\n",getpid());
	if( (pid = fork()) == -1 ){
		perror("can't fork");
		return 1;
	}
	if(pid == 0){
		if(execl("/usr/bin/man","man","ls",(char*)NULL) == -1){
			perror("Can't exec");
			return 1;
		}
	}else if(pid > 0){
		waitpid(pid, &status, 0);
		printf("Child executed status was %d\n", pid);
		printf("Its return status was %d\n", status);
	}else{
		fprintf(stderr, "Something went wrong forking\n");
		return 1;
	}
	return 0;
}
