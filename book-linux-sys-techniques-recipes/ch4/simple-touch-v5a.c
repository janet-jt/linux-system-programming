#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <linux/limits.h>

int main(int argc, char *argv[]){
	
	int errornum;
	char filename[PATH_MAX] = {0};

	if ( argc == 2 ){
		

		strncpy(filename,argv[1],sizeof(filename)-1);

		if ( creat(filename, 00644) != -1){
		
			return 0;

		}else{


			errornum = errno;
			fprintf(stderr, "Cant't create file %s\n", filename);
			fprintf(stderr, "%s\n", strerror(errornum));
			return 1;

		}


	}else{

		fprintf(stderr, "You must enter the filename as an argument.\n");		
		return 1;

	}

}
