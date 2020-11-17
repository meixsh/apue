#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

const int SIZE = 20;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("USAGE:%s filename\n", argv[0]);
		exit(1);
	}

	int fd = open(argv[1], O_RDWR | O_CREAT, 0x644);
	if (fd == -1)
	{
		perror("open(const char*, int)");
		exit(2);
	}
	int fd2 = dup(fd);

	char buf[SIZE];
	strcpy(buf, "hello world.");
	ftruncate(fd, 0);
	int len = write(fd, buf, strlen(buf));
#ifndef NDEBUG
	printf("%d %ld\n", len, lseek(fd, 0, SEEK_CUR));
#endif

	close(fd);
#ifndef NDEBUG
	printf("%d %ld\n", len, lseek(fd2, 0, SEEK_CUR));
#endif
	lseek(fd2, 0, SEEK_SET);

	printf("fd2 = %d\n", fd2);
	memset(buf, 0, SIZE);
	read(fd2, buf, len);
	printf("%s %ld\n", buf, lseek(fd2, 0, SEEK_CUR));
	close(fd2);

	return 0;
}
