#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(void){
	char rxbuf[1];
	char txbuf[3];
	int master;
	int c;

	master = posix_openpt(O_RDWR);
	grantpt(master);
	unlockpt(master);
	printf("Slave: %s \n", ptsname(master));

	while(1){
		/*read from the master fd & read 1 byte and save the content
			to rxbuf*/
		c = read(master, rxbuf, 1);
		/*check if c is equal to 1 byte*/
		if( c == 1 ){
			if( rxbuf[0] == '\r' ){
				printf("\n\r"); /* on master*/
				sprintf(txbuf, "\n\r"); /*on slave */
			}else{
				printf("%c", rxbuf[0]);
				sprintf(txbuf, "%c", rxbuf[0]);
			}
			fflush(stdout);
			write(master, txbuf, strlen(txbuf));
		}else{
			printf("disconnected\n\r");
			return 0;
		}
	}
	return 0;
}
