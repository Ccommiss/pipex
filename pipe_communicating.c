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
// Bon file 

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

	take_multiple_args(argv, ac, path);
	exit (0);
	// test lst chainees por multipipe 

	cmd1 = ft_strdup(argv[1]);
	cmd2 = ft_strdup(argv[2]);
	char **args1;
	char **args2;

	find_command(&cmd1, &args1, path);
	find_command(&cmd2, &args2, path);
	if (pid == 0)
	{
		printf ("[child] Process pid = %d and parent id %d\n", getpid(), getppid());
		dup2(fd[1], STDOUT_FILENO); //
		dup2(infile, STDIN_FILENO); //test
		close(fd[0]);
		close(fd[1]);
		execve(cmd1, args1, envp);
	}
	else
	{
		printf ("Process pid = %d and parent id %d\n", getpid(), getppid());
		dup2(fd[0], STDIN_FILENO); // on redirgine STDIN sur reading end u pipe
		dup2(outfile, STDOUT_FILENO); // ici je redirige la sortie de la commande vers outfile
		close(fd[0]);
		close(fd[1]);
		execve(cmd2, args2, envp);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
}
