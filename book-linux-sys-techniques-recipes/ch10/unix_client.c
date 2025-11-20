#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#define MAXLEN 128

int main(void){
	const char sockname[] = "/tmp/my_1st_socket";
	int fd;
	struct sockaddr_un addr;
	char sendbuffer[MAXLEN];
	char recvbuffer[MAXLEN];

	fd = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	if( fd == -1 ){
		perror("Create socket failed");
		return 1;
	}
	
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, sockname);
	
	if( (connect(fd, (const struct sockaddr*)&addr, sizeof(struct sockaddr_un))) == -1 ){
		perror("Can't connect");
		fprintf(stderr, "The server is down?\n");
		return 1;
	}

	while(1){
		printf("Message to send: ");
		fgets(sendbuffer, sizeof(sendbuffer), stdin);
		sendbuffer[strcspn(sendbuffer, "\n")] = '\0';
		if( (write(fd, sendbuffer, strlen(sendbuffer) + 1)) == -1 ){
			perror("Couldn't write");
			return 1;
		}

		if( (read(fd, recvbuffer, MAXLEN)) == -1 ){
			perror("Can't read");
			return 1;
		}
		printf("Server said: %s\n", recvbuffer);
	}
	return 0;
}
