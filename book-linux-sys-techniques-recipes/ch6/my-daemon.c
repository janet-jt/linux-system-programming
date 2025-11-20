#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>

int main(void){
	pid_t pid;
	FILE *fp;
	time_t now;
	const char pidfile[] = "/var/run/my-daemon.pid";
	const char daemonfile[] = "/tmp/my-daemon-is-alive.txt";
	
	if( (pid = fork()) == -1 ){
		perror("Can't fork!");
		return 1;
	}else if ( (pid != 0 ) ){
		exit(0);
	}

	setsid();

	if( (pid=fork()) == -1 ){
		perror("Can't fork");
		return 1;
	}else if( pid > 0 ){
		if( (fp = fopen(pidfile, "w")) == NULL ){
			perror("Can't open file for writing");
			return 1;
		}
		fprintf(fp, "%d\n", pid);
		fclose(fp);
		exit(0);
	}

	umask(022);//assigns permissions that have read/write access for files. permission: 777 - 022 = 755 of the files & dir
	chdir("/");
	if( (fp = fopen(daemonfile, "w")) == NULL ){
		perror("Can't open daemonfie");
		return 1;
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	//bc we closed the data stream (not safe) if we calls open the descriptor will call by sequence 0,1,2
	open("/dev/null", O_RDONLY);
	open("/dev/null", O_WRONLY);
	open("/dev/null", O_RDWR);

	for (;;){
		time(&now);
		fprintf(fp, "Daemon alive at %s", ctime(&now));
		fflush(fp);
		sleep(30);
	}

	return 0;

}
