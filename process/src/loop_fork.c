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
	int cnt = num;
	printf("parent pid = %d, ppid = %d: before loop fork()\n", getpid(), getppid());
	pid_t parent_pid = getpid();
	pid_t pid;
	
	while (cnt > 0)
	{
		if (getpid() == parent_pid)
		{
			pid = fork();
			if (pid == 0)
			{
				printf("%d child process is created, pid = %d, ppid = %d\n", num - cnt, getpid(), getppid());
				break;
			}
			--cnt;
		}
	}

	if (getpid() == parent_pid)
	{
		sleep(3);
		printf("parent pid = %d, ppid = %d: loop fork() complete\n", getpid(), getppid());
	}
	else
	{
		printf("%d child process is going to be end, pid = %d, ppid = %d\n", num - cnt, getpid(), getppid());
	}

	return 0;
}
