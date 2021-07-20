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


void	get_file(int *infile, int *outfile, char **argv, int ac)
{
	*infile = open(argv[1], O_RDWR);
	if (*infile == -1)
	{
		perror("Erreur");
		exit(0);
	}
	*outfile = open(argv[ac - 1], O_RDWR | O_CREAT);
	if (*outfile == - 1)
	{
		perror("Erreur");
		exit(0);
	}
}


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
	//printf ("%d pipe ont ete crees\n", j);
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
	int infile;
	int outfile;
	int **fd;
	int i;
	pid_t pid;
	t_cmd *cmds;

	get_file(&infile, &outfile, argv, ac);
	pipe_fds(&fd, ac - 4);
	cmds = take_multiple_args(argv, ac, envp);
	i = 0;
	while (cmds != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (cmds->index == 1)//premiere commande
			{ 
				if (dup2(infile, STDIN_FILENO) == - 1)
					perror("Erreur");
			}
			else
			{
				if (dup2(fd[i - 1][0], STDIN_FILENO) < 0) // ex ; cmd2 va lire fd[0][0] qui corres a la premiere cmd
				{
					perror("Erreur");
					exit(1);
				}
				close(fd[i - 1][1]);
				close(fd[i - 1][0]);
			}
			if (cmds->next == NULL) // derniere dans le cas ou deux cmd
			{
				if (dup2(outfile, STDOUT_FILENO) == -1)
					perror("Erreur");
			}
			else //pas la derniere, on dup le stdout sur l entree de la prochaine cmd
			{
				close(fd[i][0]);
				if (dup2(fd[i][1], STDOUT_FILENO) == -1)
					perror("Erreur");
				close(fd[i][1]);
			}
			execve(cmds->cmdp, cmds->cmd_args, envp);
		}
		if (i >=1)
		{
			close(fd[i - 1][1]);
			close(fd[i - 1][0]);
		}
		cmds = cmds->next;
		i++;
	}
	return (1);
}