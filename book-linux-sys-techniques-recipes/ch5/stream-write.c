#include <stdio.h>
int main(int argc, char *argv[]){
	FILE *fp;
	char linebuf[1024] = {0};
	
	if (argc != 2){
		fprintf(stderr, "Usage: %s [filename]", argv[0]);
		return 1;
	}

	if ( (fp = fopen(argv[1], "w")) == NULL ){
		perror("Cannot open file to write");
		return 1;
	}

	while(fgets(linebuf, sizeof(linebuf), stdin) != NULL){
		fprintf(fp, linebuf);
	}

	fclose(fp);
	return 0;
}
