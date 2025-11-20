#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]){

	if( argc != 2){

		fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
		return 1;

	}

	if( unlink(argv[1]) == -1 ){

		perror("Can't remove the file");
		return errno;

	}

	return 0;

}
