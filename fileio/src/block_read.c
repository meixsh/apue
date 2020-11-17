#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define BUF_SIZE 10

int main(int argc, char *argv[])
{
	char buf[BUF_SIZE];
	int len = read(STDIN_FILENO, buf, BUF_SIZE);
	if (len == -1)
	{
		perror("read STDIN_FILENO");
		exit(1);
	}
	
	write(STDOUT_FILENO, buf, len);

	return 0;
}
