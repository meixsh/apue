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
	int n;
	int fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
	if (fd < 0)
	{
		perror("open /dev/tty");
		exit(1);
	}

tryagain:
	n = read(fd, buf, BUF_SIZE);
	if (n < 0)
	{
		if (errno == EAGAIN)
		{
			sleep(3);
			write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
			goto tryagain;
		}
		perror("read /dev/tty");
		exit(1);
	}
	write(STDOUT_FILENO, buf, n);
	close(fd);

	return 0;
}
