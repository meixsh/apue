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
	pid_t arr[3];
	int i;

	for (i = 0; i < 3; ++i)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			break;
		}
		arr[i] = pid;
	}

	if (i == 0)
	{
		printf("child %d: pid = %d\n", i, getpid());
		execlp("ps", "ps", "au", NULL);
		perror("execlp(ps)");
		exit(2);
	}
	else if (i == 1)
	{
		printf("child %d: pid = %d\n", i, getpid());
		execl("/home/meixsh/workspace/apue/process/obj/hello", "hello", NULL);
		perror("execlp(ps)");
		exit(3);
	}
	else if (i == 2)
	{
		printf("child %d: pid = %d\n", i, getpid());
		char *p = "hello";
		p[0] = 'b';
		exit(4);
	}
	else if (i == 3)
	{
		int wstatus = 0;
		for (int i = 0; i < 3; ++i)
		{
			pid_t wpid = waitpid(arr[i], &wstatus, 0);
			if (WIFEXITED(wstatus))
			{
				printf("child %d pid %d: term normally, term code %d\n", i, wpid, WEXITSTATUS(wstatus));
			}
			else if (WIFSIGNALED(wstatus))
			{
				printf("child %d pid %d: term signal, term code %d\n", i, wpid, WTERMSIG(wstatus));
			}
			else
			{
				printf("child %d pid %d: term uk, term code uk\n", i, wpid);
			}
		}
	}
	else 
	{
		printf("undefined behaviour.\n");
		exit(1);
	}

	return 0;
}
