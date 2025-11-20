#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 4096

int main ( int argc, char* argv[] ){

	int fd;
	struct stat fileinfo;
	off_t filesize;
	int maxread;
	char buf[MAXSIZE] = {0};

	if( argc != 4){
		fprintf(stderr, "Usage: %s [filename] [position] [byte to read]\n", argv[0]);
		return 1;
	}

	if( ( fd = open(argv[1], O_RDONLY) ) == -1 ){
		perror("Cannot open the file");
		return errno;
	}

	fstat(fd, &fileinfo);
	filesize = fileinfo.st_size;

	if( filesize >= MAXSIZE )
		maxread = MAXSIZE-1;
	else
		maxread = filesize;
	
	if( lseek(fd, atoi(argv[2]), SEEK_SET) == -1 ){
		perror("Cannot move to the position");
		return errno;
	}

	if( read(fd, buf, atoi(argv[3]) ) == -1 ){
		perror("Cannot read the file");
		return errno;
	}

	if( write(1, buf, strlen(buf)) == -1 ){
		perror("Cannot show the content");
		return errno;
	}
	
	return 0;

}
