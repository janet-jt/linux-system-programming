#include <stdio.h>

int main(int argc, char *argv[]){
	FILE *fp;
	char linebuffer[1024];

	if( argc != 2 ){
		fprintf(stderr, "Usage: %s [filename]", argv[0]);
		return 1;
	}

	if ( (fp = fopen(argv[1], "r")) == NULL ){
		perror("Cannot open the file to read");
		return 1;
	}

	while( fgets(linebuffer, sizeof(linebuffer), fp) != NULL){
		printf("%s", linebuffer);
	}
	
	fclose(fp);
	return 0;
}
