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
	int fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();
	char *cmd1;
	char *cmd2;

	int infile = open("./infile", O_RDWR);
	int outfile = open("./outfile", O_RDWR);

	cmd1 = malloc(sizeof(char) * 100);
	bzero(cmd1, strlen(argv[1]) + 5);
	cmd1 = strcat(cmd1, "/bin/");
	cmd1 = strcat(cmd1, argv[1]);

	if (ac > 2)
	{
		cmd2 = malloc(sizeof(char) * 100);
		bzero(cmd2, strlen(argv[2]) + 5);
		cmd2 = strcat(cmd2, "/bin/");
		cmd2 = strcat(cmd2, argv[2]);
	}

	if (pid == 0)
	{
		//child process
		dup2(fd[1], STDOUT_FILENO); // on redirige le STDOUT sur writing end du pipe
		close(fd[0]);
		close(fd[1]);
		execve(cmd1, NULL, envp);
	}

	int pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO); // on redirgine STDIN sur reading end u pipe
		close(fd[0]);
		close(fd[1]);
		if (ac > 2)
			execve(cmd2, NULL, envp);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}