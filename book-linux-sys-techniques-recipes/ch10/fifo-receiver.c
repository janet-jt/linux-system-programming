#include <stdio.h>
int main(void){
	FILE *fp;
	signed char c;
	const char fifoname[] = "/home/janet/Desktop/new-job/linux-system-programming/ch10/my-2nd-fifo";
	if( (fp = fopen(fifoname, "r")) == NULL ){
		perror("Can't open FIFO");
		return 1;
	}
	while( (c = getc(fp)) != EOF )
		putchar(c);
	fclose(fp);
	return 0;
}
