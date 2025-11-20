#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE *fp;
	//char linebuffer[1024];
	char ch;

	if( argc < 3 || argc > 4 ){
		fprintf(stderr, "Usage: %s [filename] [start pos] [end pos]", argv[0]);
		return 1;
	}

	if ( (fp = fopen(argv[1], "r")) == NULL ){
		perror("Cannot open the file to read");
		return 1;
	}

	fseek(fp, atoi(argv[2]), SEEK_SET);
	
	while( (ch = fgetc(fp)) != EOF){
		if( argv[3] != NULL ){
			if( ftell(fp) >= atoi(argv[3]) ){
				break;
			}
			putchar(ch);
		}
	}
	printf("\n");
	fclose(fp);
	return 0;
}
