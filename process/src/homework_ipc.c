#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int fd = open("temp", O_RDWR | O_CREAT, 0644);	
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}

	pid_t pid = fork();
	if (pid == 0)
	{
		// child read
		char buf[8] = {0};
//		char buf2[16] = {0};
//		int n;
//		printf("child: pid = %d, ppid = %d\n", getpid(), getppid());
		sleep(1);
		lseek(fd, 0, SEEK_SET);
		while (read(fd, buf, sizeof(buf) - 1))
		{
		//	printf("%d\n", n);
			printf("%s", buf);
//			strcat(buf2, buf);
			memset(buf, 0, sizeof(buf) - 1);
		}
//		printf("buf2:%s\n", buf2);
		close(fd);
	}
	else if (pid > 0)
	{
		// parent write
		char buf[] = "hello world.";
		write(fd, buf, sizeof(buf));
		sleep(3);
//		wait(NULL);
//		printf("parent: pid = %d\n", getpid());
		close(fd);
	}
	else 
	{
		perror("fork");
		exit(2);
	}

	return 0;
}
