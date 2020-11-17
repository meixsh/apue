#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define NDEBUG

void traverse_dir(DIR *, const char *);
void print_file_info(const char *filename);
DIR* open_dir(const char *);
void get_file_type(mode_t, char *);
void get_file_perm(mode_t, char *);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("USAGE:%s %s\n", argv[0], "pathname");
		exit(1);
	}
	
	if (argv[1][strlen(argv[1]) -1 ] != '/')
	{
		printf("pathname must endwith '/'\n");
		exit(4);
	}

	char fullPath[512] = {0};
	strcpy(fullPath, argv[1]);

	DIR *pd = open_dir(fullPath);

	traverse_dir(pd, fullPath);

	return 0;
}

void traverse_dir(DIR *pd, const char *parentPath)
{
	struct dirent *pdent = NULL;
	while ((pdent = readdir(pd)) != NULL)  
	{
		unsigned char d_type = pdent->d_type;
		char *filename = pdent->d_name;
		char fullPath[512] = {0};
		strcat(fullPath, parentPath);
		strcat(fullPath, filename);
#ifndef NDEBUG
		printf("filename:%s\n", fullPath);
#endif
		if (d_type == DT_DIR)
		{
			print_file_info(fullPath);
			printf("%s\n", filename);
			if ((strcmp(filename, ".") == 0) || (strcmp(filename, "..") == 0))
			{
				continue;
			}
			strcat(fullPath, "/");
			traverse_dir(open_dir(fullPath), fullPath);
		}
		else if (d_type == DT_UNKNOWN)
		{
			printf("traverse_dir(DIR *): UNKNOWN file.\n");
		}
		else
		{
			print_file_info(fullPath);
			printf("%s\n", filename);
		}
	}
	
	closedir(pd);

	return;	
}

void print_file_info(const char *filename)
{
	struct stat st;

	if (stat(filename, &st) == -1)
	{
		perror("stat(const char*, struct stat*)");
#ifndef NDEBUG
		printf("%s\n", filename);
#endif
		exit(3);
	}

	off_t size = st.st_size;
	char fmode[11] = {0};
	get_file_type(st.st_mode, fmode);
	get_file_perm(st.st_mode, fmode);

	printf("%s %ld %ld ", fmode, st.st_nlink, size);
}

DIR* open_dir(const char *pathname)
{
	DIR *pd = opendir(pathname);
	if (pd == NULL)
	{
		perror("opendir(const char*)");
		exit(2);
	}
	return pd;
}

void get_file_type(mode_t mode, char *fmode)
{
	switch (mode & S_IFMT)	
	{
		case S_IFSOCK: 
			fmode[0] = 's';
			break;
		case S_IFLNK:
			fmode[0] = 'l';
			break;
		case S_IFREG:
			fmode[0] = '-';
			break;
		case S_IFBLK:
			fmode[0] = 'b';
			break;
		case S_IFDIR:
			fmode[0] = 'd';
			break;
		case S_IFCHR:
			fmode[0] = 'c';
			break;
		case S_IFIFO:
			fmode[0] = 'p';
			break;
		default:
			fmode[0] = 'T'; // T stands for trash, means no meaning value.
			break;
	}

	return;
}

void get_file_perm(mode_t mode, char *fmode)
{
	mode_t op = mode & S_IRWXO;
	mode_t gp = mode & S_IRWXG;
	mode_t up = mode & S_IRWXU;

	if (op & S_IXOTH)
		fmode[9] = 'x';
	if (op & S_IWOTH)
		fmode[8] = 'w';
	if (op & S_IROTH)
		fmode[7] = 'r';

	if (gp & S_IXGRP)
		fmode[6] = 'x';
	if (gp & S_IWGRP)
		fmode[5] = 'w';
	if (gp & S_IRGRP)
		fmode[4] = 'r';

	if (up & S_IXUSR)
		fmode[3] = 'x';
	if (up & S_IWUSR)
		fmode[2] = 'w';
	if (up & S_IRUSR)
		fmode[1] = 'r';

	return;
}






