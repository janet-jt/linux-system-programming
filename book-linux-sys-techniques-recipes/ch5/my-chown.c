#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

int main (int argc, char* argv[]){

	struct group *grpinfo;
	struct passwd *userinfo;
	char *username = { 0 };
	char *grpname = { 0 };
	unsigned int uid, gid;

	if( argc != 3 ){
		
		fprintf(stderr, "Usage: %s [user][:group] [path]\n", argv[0]);
		return 1;

	}

	//start to search the first token
	username = strtok(argv[1],":");
	//printf("%s\n", username);
	
	if( (userinfo = getpwnam(username)) == NULL ){
		printf("Error: Cannot find the user - %s\n", strerror(errno));
		return errno;
	}
	
	uid = userinfo->pw_uid;
	//printf("%u\n",uid);

	//NULL means the function strtok() continues tokenizing the string I passed in first
	//So first call --> first token, second call (with NULL specified) --> second token, and so on
	if( grpname = strtok(NULL,":") ){
		//printf("%s\n", grpname);

		if( (grpinfo = getgrnam(grpname)) == NULL ){
			printf("Error: Cannot find the group - %s\n", strerror(errno));
			return errno;
		}

		gid = grpinfo->gr_gid;
		//printf("%u\n",gid);
		
	}else{
		gid = -1;
	}


	if( chown(argv[2],uid,gid) == -1 ){
			
		printf("Error: Cannot execute chown - %s\n", strerror(errno));
		return errno;
	}

	return 0;
}
