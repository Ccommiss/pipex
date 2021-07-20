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

void pipe_fds(int ***fd, int pipes)
{
	*fd = malloc(sizeof(int *) * pipes);
	int j = 0;

	while (j < pipes)
	{
		fd[0][j] = malloc(sizeof(int) * 2);
		pipe(fd[0][j]);
		j++;
	}
	printf ("%d pipe ont ete crees\n", j);
}

/*
**		> Creation double tab to handle X pipe of
**		int[2]
**
**     fd[0][0/1]       fd[2][0/1]
**        v                 v
**	cmd1  |  cmd2  |  cmd3  |  cmd4  |  cmd5
**             	   ^                 ^
**          	fd[1][0/1]             fd[3][0/1]
*/

int main(int ac, char **argv, char **envp)
{
	int infile = open(argv[1], O_RDWR);
	int outfile = open(argv[ac - 1], O_RDWR);
	printf ("fd infile %d outfile %d \n", infile, outfile);
	int **fd;
	int i = 0;
	pid_t pid;
	pid_t pid2;
	char *path;
	t_cmd *cmds;
	int status;

	pipe_fds(&fd, ac - 4);
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	path = ft_strdup(envp[i]);

	cmds = take_multiple_args(argv, ac, path);
	i = 0;
	while (cmds != NULL)
	{
		printf("tour = %d \n", cmds->index);
		sleep(1);
		pid = fork();
		printf("[process] = %d Cooking command [%s] \n", pid, cmds->cmdp);
		if (pid == 0)
		{
			printf("[Process %d - child of %d]\n", getpid(), getppid());
			printf("CMD TO EXEC = %s \n", cmds->cmdp);
			sleep(1);
			if (cmds->index == 1)
			{ //premiere commande
				if (dup2(infile, STDIN_FILENO) == - 1)
					perror ("==> Error dup2\n");
				printf("Duping first command\n");
			}
			else
			{
				printf("duping input from pipe = %d %d\n", fd[i - 1][0], fd[i - 1][1]);
				if (dup2(fd[i - 1][0], STDIN_FILENO) < 0) // ex ; cmd2 va lire fd[0][0] qui corres a la premiere cmd
				{
					perror("FAILS DUP\n");
					exit(1);
				}
				dprintf(STDERR_FILENO, "else : on a dup l'entree\n");
				close(fd[i - 1][1]);
				close(fd[i - 1][0]);
			}
			dprintf(STDERR_FILENO, "on a dup l'entree\n");
			if (cmds->next == NULL) // derniere dans le cas ou deux cmd
			{
				printf("[%d %d] Duping the last command %d\n", pid, getpid(), i);
				if (dup2(outfile, STDOUT_FILENO) == -1)
					perror ("==> Error dup2\n");
			}
			else //pas la derniere, on dup le stdout sur l entree de la prochaine cmd
			{
				close(fd[i][0]);
				printf("Duping output for the next pipe %d %d\n", fd[i][0], fd[i][1]);
				if (dup2(fd[i][1], STDOUT_FILENO) == -1)
					perror ("==> Error dup2\n");
				close(fd[i][1]);
			}
			dprintf(STDERR_FILENO, "Closing i - 1 = %d \n", i-1);
			dprintf(STDERR_FILENO,"exec %s \n", cmds->cmdp);
			execve(cmds->cmdp, cmds->cmd_args, envp);
			dprintf(STDERR_FILENO,"Normally its dead\n");
		}
		sleep(1);
		if (i >=1)
		{
			close(fd[i - 1][1]);
			close(fd[i - 1][0]);
		}
		write(1, "he\n", 4);
		write(1, "yo\n", 4);
		cmds = cmds->next;
		printf("_________\n");
		i++;
	}
	printf("ici \n");
	// close(fd[0][0]);
	// close(fd[0][1]);
	// close(fd[1][0]);
	// close(fd[1][1]);

	return (1);
}

// void old_code()
// {
// 	cmd1 = ft_strdup(argv[1]);
// 	cmd2 = ft_strdup(argv[2]);
// 	char **args1;
// 	char **args2;

// 	find_command(&cmd1, &args1, path);
// 	find_command(&cmd2, &args2, path);
// 	if (pid == 0)
// 	{
// 		printf ("[child] Process pid = %d and parent id %d\n", getpid(), getppid());
// 		dup2(fd[1], STDOUT_FILENO); //
// 		dup2(infile, STDIN_FILENO); //test
// 		close(fd[0]);
// 		close(fd[1]);
// 		execve(cmd1, args1, envp);
// 	}
// 	else
// 	{
// 		printf ("Process pid = %d and parent id %d\n", getpid(), getppid());
// 		dup2(fd[0], STDIN_FILENO); // on redirgine STDIN sur reading end u pipe
// 		dup2(outfile, STDOUT_FILENO); // ici je redirige la sortie de la commande vers outfile
// 		close(fd[0]);
// 		close(fd[1]);
// 		execve(cmd2, args2, envp);
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid, NULL, 0);
// }
