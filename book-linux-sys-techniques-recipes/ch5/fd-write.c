#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <linux/limits.h>

int main ( int argc, char* argv[]){

	int pfd;

	if( argc != 3 ){

		fprintf(stderr, "Usage: %s [file path] [string]",argv[0]);
		return 1;

	}

	if( (pfd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 00644 )) == -1  ){

		perror("Cannot open the file!");
		return errno;

	}


	if( write(pfd,argv[2],strlen(argv[2])) == -1){

		perror("Cannot write the file!");
		return errno;

	}
	
	close(pfd);

	return 0;

}
