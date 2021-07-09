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
#include "pipex.h"
#define _POSIX_SOURCE

void find_command(char **cmd, char ***args, char *path);


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

	char *path;
	int i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	path = ft_strdup(envp[i]);
	cmd1 = ft_strdup(argv[1]);
	cmd2 = ft_strdup(argv[2]);
	char **args1;
	char **args2;

	find_command(&cmd1, &args1, path);
	find_command(&cmd2, &args2, path);
	// execve(cmd1, args1, envp);
	// execve(cmd2, args2, envp);
	if (pid == 0)
	{
		//child process
		dup2(fd[1], STDOUT_FILENO); // on redirige le STDOUT sur writing end du pipe
		//dup2(infile, STDOUT_FILENO); // on redirige le STDOUT sur writing end du pipe

		close(fd[0]);
		close(fd[1]);
		execve(cmd1, args1, envp);
	}

	int pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO); // on redirgine STDIN sur reading end u pipe
		//dup2(outfile, STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(cmd2, args2, envp);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}
