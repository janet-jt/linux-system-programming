#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
int main(void){
	char mypass[] = "super-secret";
	char buffer[80];
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	/*using the current setting & no echo*/
	term.c_lflag = term.c_lflag & ~ECHO;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);

	printf("Enter password: ");
	scanf("%s", buffer);
	if( (strcmp(mypass,buffer) == 0) ){
		printf("\nCorrect password, welcome!\n");
	}else{
		printf("\nIncorrect password, go away!\n");
	}

	term.c_lflag = term.c_lflag | ECHO;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
	return 0;
}
