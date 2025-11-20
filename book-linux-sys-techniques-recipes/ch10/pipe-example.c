#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MAX 128
int main(void){
	int pipefd[2] = {0};
	pid_t pid;
	char line[MAX];

	if( (pipe(pipefd)) == -1){
		perror("Can't create pipe");
		return 1;
	}
	if( (pid = fork()) == -1 ){
		perror("Can't fork");
		return 1;
	}
	if( pid > 0 ){
		close(pipefd[0]);
		dprintf(pipefd[1], "Hello from parent");
	}else{
		close(pipefd[1]);
		read(pipefd[0], line, MAX-1);
		printf("%s\n", line);
	}
	return 0;
}
