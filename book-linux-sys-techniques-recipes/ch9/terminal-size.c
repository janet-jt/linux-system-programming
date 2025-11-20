#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
int main(void){
	struct winsize termsize;
	while(1){
		//printf("\033[;1H\033[2J");
		/*Blink the Hello Message -> man 4 console_codes*/
		printf("\033[35;5mHello!\033[0m\n");
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &termsize);
		printf("Height: %d rows\n", termsize.ws_row);
		printf("Width: %d cols\n", termsize.ws_col);
		sleep(0.1);
	}
	return 0;
}
