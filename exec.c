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
#include <stdlib.h>
#define _POSIX_SOURCE

int main(int ac, char **argv, char **envp)
{

	int i = 0;
	char *cmd1;
	char cmd2[30];

	int fd[2];
	int status;
	if (pipe(fd) == -1)
		return 0;
	int id = fork();

	if (id == 0) // processs FILS BVA ECRIRE
	{
		printf ("from dad id = %d\n", id);
		close(fd[0]);

		//; // on duplique fd 1
		printf("%s\n", argv[1]);
		cmd1 = malloc(sizeof(char) * 100);
		bzero(cmd1, strlen(argv[1]) + 5);
		cmd1 = strcat(cmd1, "/bin/");
		cmd1 = strcat(cmd1, argv[1]);
		printf("cmd1 = %s\n", cmd1);
		//cmd2 = strcat("/bin/", argv[2]);
		// for (int j = 0; argv[j]; j++)
		// 	printf ("%s \n", argv[j]);
		execve(cmd1, argv + 1, envp);
		printf("icwrgtwrtti \n");
		write(fd[1], "LOjwkjwL\n", 10);
		close(fd[1]);
	}
	else
	{
		int newfd;
		if ((newfd = open("./outfile", O_RDWR)) < 0)
			perror("open");
		printf ("from child\n");
		char buffer[100];
		int ret;

		bzero(buffer, 100);

		close(fd[1]); //ferme write side
		ret = read(fd[0], buffer, 99);
		dup2(newfd, fd[1]);
		buffer[ret] = 0;

		printf ("recu : %s \n", buffer);
		close(fd[0]);

	}
	//printf("[Error nb %d]\n %s \n", errno, strerror(errno));
}
