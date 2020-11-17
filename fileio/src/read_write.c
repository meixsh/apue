#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("USAGE: %s %s %s\n", argv[0], "srcfile", "dstfile");
		exit(1);
	}
	
	const char *srcfile = argv[1];
	const char *dstfile = argv[2];

	int srcfd = open(srcfile, O_RDONLY);
	int dstfd = open(dstfile, O_WRONLY | O_CREAT, 0664);

	if (srcfd == -1 || dstfd == -1)
	{
		perror("open failed");
		exit(1);
	}

	char buf[1024 * 8];
	int len;
	int wlen;
	while ((len = read(srcfd, buf, sizeof(buf))) > 0)
	{
		wlen = write(dstfd, buf, len);
	}

	if (len == -1 || wlen == -1)
	{
		perror("read or write failed");
	}

	close(srcfd);
	close(dstfd);

	return 0;
}
