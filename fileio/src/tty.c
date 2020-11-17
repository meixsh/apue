#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#define MSG_TRY "try again\n"
#define BUF_SIZE 10

int main()
{
	char buf[BUF_SIZE];
	char buf1[BUF_SIZE];
	int n, m;
	int fd = open("/dev/tty", O_RDWR);
	if (fd < 0)
	{
		perror("open /dev/tty");
		exit(1);
	}

	n = read(fd, buf, BUF_SIZE);
	m = read(STDIN_FILENO, buf1, BUF_SIZE);
	write(fd, buf, n);
	write(STDOUT_FILENO, buf1, m);


	close(fd);
	return 0;
}
