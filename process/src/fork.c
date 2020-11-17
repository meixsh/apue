#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	
	for (int i = 0; i < 5; ++i)
	{
		printf("before fork: i = %d\n", i);
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork()");
		exit(1);
	}
	else if (pid > 0)
	{
		printf("ret = %d, pid = %d\n", pid, getpid());	
	}
	else
	{
		printf("ret = %d, pid = %d, ppid = %d\n", pid, getpid(), getppid());
	}

	for (int i = 0; i < 5; ++i)
	{
		printf("after fork: i = %d\n", i);
	}

	return 0;
}
