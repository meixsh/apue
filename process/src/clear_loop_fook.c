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
	if (argc < 2)
	{
		printf("USAGE:%s number_of_child", argv[0]);
		exit(1);
	}

	int num = atoi(argv[1]);
	printf("parent: pid = %d, ppid = %d: before loop fork()\n", getpid(), getppid());
	pid_t pid;
	int i = 0;

	for (i = 0; i < num; ++i)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("%d child process is created, pid = %d, ppid = %d\n", i, getpid(), getppid());
			break;
		}
	}

	if (i == num)
	{
		sleep(2);
		printf("parent: pid = %d, ppid = %d: loop fork() complete\n", getpid(), getppid());
	}
	else
	{
		printf("%d child process is going to be end, pid = %d, ppid = %d\n", i, getpid(), getppid());
	}

	return 0;
}
