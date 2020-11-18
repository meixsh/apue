#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	pid_t pid = fork();

	if (pid == 0)
	{
		printf("child: pid = %d, ppid = %d\n", getpid(), getppid());
		sleep(10);
		printf("child: pid = %d, ppid = %d\n", getpid(), getppid());
	}
	else if (pid > 0)
	{
		printf("parent: pid = %d, cpid= %d\n", getpid(), pid);
		int status;
		pid_t ret = wait(&status);

		printf("parent: ret = %d, status = %d\n", ret, status);
		if (WIFEXITED(status))
		{
			printf("terminated normally, exit code: %d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			printf("terminated signal, signal code: %d\n", WTERMSIG(status));
		}
		else 
		{
			printf("terminated by other ways.\n");
		}
	}
	else 
	{
		perror("fork");
		exit(1);
	}

	return 0;
}
