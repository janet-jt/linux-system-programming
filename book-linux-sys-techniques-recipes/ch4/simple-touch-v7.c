#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <linux/limits.h>

int main(int argc, char *argv[]){

	char filename[PATH_MAX] = {0};

	if( argc != 2){

		fprintf(stderr, "You have to enter the filename as an argument\n");
		return 1;

	}

	strncpy(filename, argv[1], sizeof(filename)-1);

	if( creat(filename, 00644) == -1 ){

		perror("Cannot create the file\n");
		return errno;

	}

	return 0;

}

