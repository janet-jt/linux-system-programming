#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

int main(void){
	printf("My PID is %d\n", getpid());
	printf("Hit enter to continue ");
	getchar();
	printf("Executing /usr/bin/less...\n");
	if(execl("/usr/bin/less","less","/etc/passwd", (char*)NULL) == -1){
	//if(execl("/usr/bin/chmod","chmod","777","test.txt", (char*)NULL) == -1){
		perror("Can't execute program");
		return 1;
	}
	return 0;
}
