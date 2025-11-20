#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <utime.h>
#include <linux/limits.h>

int main(int argc, char *argv[]){

	char filename[PATH_MAX] = {0};

	if( argc != 2 ){

		fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
		return 1;

	}

	strncpy(filename, argv[1], sizeof(filename)-1);
	
	if( utime(filename, NULL) == -1 ){
		
		if( errno == ENOENT ){

			if( creat(filename, 00644) == -1 ){

				perror("Can't create the file");
				return errno;

			}

		}else{

			perror("Can't update timestamp");
			return errno;

		}
	}

	return 0;

}
