#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <getopt.h>
#include <string.h>
#include <linux/limits.h>
void printUsage(char progname[], FILE *fp);
int main(int argc, char *argv[]){
	FILE *fp;
	FILE *procfp;
	int pid, opt;
	int killit = 0;
	char procpath[PATH_MAX] = { 0 };
	char cmdline[PATH_MAX] = { 0 };
	const char pidfile[] = "/var/run/my-daemon.pid";
	const char daemonPath[] = "/usr/local/sbin/my-daemon-v2";
	//const char daemonPath[] = "my-daemon-v2";

	while((opt = getopt(argc, argv, "kh")) != -1){
		switch(opt){
			case 'k':
				killit = 1;
				break;
			case 'h':
				printUsage(argv[0], stdout);
				return 0;
			default:
				printUsage(argv[0], stdout);
				return 1;
		}
	}

	if( (fp = fopen(pidfile, "r")) == NULL ){
		perror("can't open PID-file (daemon isn't running?)");
		return 1;
	}

	if( (fscanf(fp, "%d", &pid)) != 1 ){
		fprintf(stderr, "can't read PID from %s\n");
		return 1;
	}
	
	sprintf(procpath, "/proc/%d/cmdline", pid);

	if( (procfp = fopen(procpath, "r")) == NULL ){
		perror("can't open /proc path (no /proc or wrong PID?)");
		return 1;
	}

	fscanf(procfp, "%s", cmdline);

	if( (strncmp(cmdline, daemonPath, PATH_MAX)) != 0 ){
		fprintf(stderr, "PID %d doesn't belong to %s\n", pid, daemonPath);
		return 1;
	}

	if( killit == 1 ){
		if( (kill(pid, SIGTERM)) == 0 ){
			printf("Successfully terminated my-daemon-v2\n");
		}else{
			perror("couldn't terminate my-daemon-v2");
			return 1;
		}
	}else{
		printf("The daemon is running with PID %d\n", pid);
	}
	return 0;

}

void printUsage(char progname[], FILE *fp){
	fprintf(fp, "Usage: %s [-k] [-h]\n", progname);
	fprintf(fp, "If no options are given, a status message is displayed.\n -k will terminate the daemon.\n-h will display this usage help\n");
}
