#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

void cleanUp(int signum);
int fd; //the FIFO file descriptor
const char fifoname[] = "/home/janet/Desktop/new-job/linux-system-programming/ch10/my-2nd-fifo";
int main(int argc, char *argv[]){
	struct sigaction action;
	if( argc != 2 ){
		fprintf(stderr, "Usages: %s 'the message'\n", argv[0]);
		return 1;
	}
	action.sa_handler = cleanUp;
	sigfillset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGTERM, &action, NULL);
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	sigaction(SIGABRT, &action, NULL);
	sigaction(SIGPIPE, &action, NULL);
	if( (mkfifo(fifoname, 0644)) != 0 ){
		perror("Can't create FIFO");
		return 1;
	}
	if( (fd = open(fifoname, O_WRONLY)) == -1 ){
		perror("Can't open FIFO");
		return 1;
	}
	while(1){
		dprintf(fd, "%s\n", argv[1]);
		sleep(1);
	}
	close(fd);
	unlink(fifoname);
	return 0;
}

void cleanUp(int signum){
	if( signum == SIGPIPE )
		printf("The receiver stopped receiving\n");
	else
		printf("Aborting...\n");
	if( (close(fd)) == -1 )
		perror("Can't close file descriptor");
	if( (unlink(fifoname)) == -1 ){
		perror("Can't remove FIFO");
		exit(1);
	}
	exit(0);
}
