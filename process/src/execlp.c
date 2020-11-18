#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	pid_t pid = fork();
	if (pid == 0)
	{
		execlp("sl", "sl", NULL);	
		perror("execlp");
		exit(1);
	}

	for (int i = 0; i < 3; ++i)
	{
		printf("parent: %d\n", i);
	}

	return 0;
}
