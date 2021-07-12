#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#define _POSIX_SOURCE

int main(void)
{
	int fd[2];
	int status;
	if (pipe(fd) == -1)
		return 0;
	int id = fork();

	if (id == 0)
	{
		printf("in da child\n");
		close(fd[0]);
		printf("close child\n");
		int x;
		printf("id = %d\n", id);
		printf("input a nb :\n");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
	}
	else
	{
		printf("in da daddy\n");
		//wait(&status);
		close(fd[1]);
		printf("close daddy\n");

		int y;
		read(fd[0], &y, sizeof(int));
		printf("read daddy\n");

		close(fd[0]);
		printf("id = %d\n", id);
		printf("got from child %d \n", y);
	}
}
