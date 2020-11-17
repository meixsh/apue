#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>


void get_file_type(mode_t mode, char *fmode);
void get_file_perm(mode_t mode, char *fmode);

/**
 * myls filename
 * -rwxrwxrwx
 */
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("USAGE: %s %s\n", argv[0], "filename");
		exit(1);
	}

	const char *filename = argv[1]; 
	char fmode[11];
	struct stat st;
	mode_t mode;

	if (stat(filename, &st) == -1)
	{
		perror("stat(const char*, sturct *stat)");
		exit(1);
	}

	mode = st.st_mode;
	memset(fmode, '-', 10);
	fmode[10] = 0;

	get_file_type(mode, fmode);
	get_file_perm(mode, fmode);

	printf("%s\n", fmode);

	return 0;
}

void get_file_type(mode_t mode, char *fmode)
{
	switch (mode & S_IFMT)	
	{
		case S_IFSOCK: 
			fmode[0] = 's';
			break;
		case S_IFLNK:
			fmode[0] = 'l';
			break;
		case S_IFREG:
			fmode[0] = '-';
			break;
		case S_IFBLK:
			fmode[0] = 'b';
			break;
		case S_IFDIR:
			fmode[0] = 'd';
			break;
		case S_IFCHR:
			fmode[0] = 'c';
			break;
		case S_IFIFO:
			fmode[0] = 'p';
			break;
		default:
			fmode[0] = 'T'; // T stands for trash, means no meaning value.
			break;
	}

	return;
}

void get_file_perm(mode_t mode, char *fmode)
{
	mode_t op = mode & S_IRWXO;
	mode_t gp = mode & S_IRWXG;
	mode_t up = mode & S_IRWXU;

	if (op & S_IXOTH)
		fmode[9] = 'x';
	if (op & S_IWOTH)
		fmode[8] = 'w';
	if (op & S_IROTH)
		fmode[7] = 'r';

	if (gp & S_IXGRP)
		fmode[6] = 'x';
	if (gp & S_IWGRP)
		fmode[5] = 'w';
	if (gp & S_IRGRP)
		fmode[4] = 'r';

	if (up & S_IXUSR)
		fmode[3] = 'x';
	if (up & S_IWUSR)
		fmode[2] = 'w';
	if (up & S_IRUSR)
		fmode[1] = 'r';

	return;
}
