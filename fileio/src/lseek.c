#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int fd = open("test.txt", O_RDWR);
	off_t offset;
	offset = lseek(fd, 0, SEEK_SET);
	printf("%ld\n", offset);
	offset = lseek(fd, 100, SEEK_SET);
	printf("%ld\n", offset);
	offset = lseek(fd, 0, SEEK_CUR);	
	printf("%ld\n", offset);
	offset = lseek(fd, 0, SEEK_END);
	printf("%ld\n", offset);
	offset = lseek(fd, 100, SEEK_END);
	printf("%ld\n", offset);
//	write(fd, "a", 1);
//	printf("%ld\n", offset);

	return 0;
}
