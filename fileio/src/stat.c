#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("USAGE: %s %s\n", argv[0], "filename");
		exit(1);
	}

	struct stat st;
	memset(&st, 0, sizeof(st));
	int ret = stat(argv[1], &st);
	if (ret == -1)
	{
		perror("stat(const char*, struct stat)");
		exit(1);
	}

	printf("size of %s: %ld\n", argv[1], st.st_size);

	return 0;
}
