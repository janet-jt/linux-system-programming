#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

int main( int argc, char *argv[]){

	struct stat filestat;
	struct passwd *userinfo;
	struct group *grpinfo;

	if( argc != 2 ){

		fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
		return 1;

	}

	if ( stat(argv[1], &filestat) == -1){

		fprintf(stderr, "Can't not read the file %s: %s\n", argv[1], strerror(errno));
		return errno;

	}

	
	if( (userinfo = getpwuid(filestat.st_uid)) == NULL ){

		fprintf(stderr, "Can't find the user: %s\n", strerror(errno));
		return errno;

	}

	
	if( (grpinfo = getgrgid(filestat.st_gid)) == NULL ){

		fprintf(stderr, "Can't find the group: %s\n", strerror(errno));
		return errno;

	}

	printf("indoe: %lu\n", filestat.st_ino);
	printf("Size: %zd\n", filestat.st_size);
	printf("Link: %lu\n", filestat.st_nlink);
	printf("User: %d (%s)\n", userinfo->pw_uid, userinfo->pw_name);
	printf("Group: %d (%s)\n", grpinfo->gr_gid, grpinfo->gr_name);
	printf("File mode: %d\n", filestat.st_mode);

	return 0;

}
