#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int fd = open("hello", O_RDWR | O_CREAT, 0777);
	if (fd == -1)
	{
		printf("open failed!\n");
	}
	close(fd);

	return 0;
}
