#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void){
	pid_t pid;
	printf("My PID is %d\n", getpid());
	if( (pid = fork()) == -1 ){
		perror("Can't fork");
		return 1;
	}
	if(pid == 0){
		printf("Hellp from the child process!\n");
		sleep(120);
	}else if(pid > 0){
		printf("Hello from the parent process! My child has PID %d\n", pid);
		//sleep(120);
		execl("/usr/bin/less","less","/etc/passwd", (char*)NULL);
	}else{
		fprintf(stderr,"Something went wrong forking\n");
		return 1;
	}
	return 0;
}
