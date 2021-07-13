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
	int outfile = open(argv[ac], O_RDWR);
	int **fd;
	int i = 0;
	pid_t pid;
	pid_t pid2;
	char *path;
	t_cmd *cmds;
	int status;

	fd = malloc(sizeof(int *) * ac - 4);
	int j = 0;
	while (j < ac - 4)
	{
		fd[j] = malloc(sizeof(int) * 2);
		fd[j][0] = 9;
		j++;
	}
	j = 0;

	while (j < ac - 4)
	{
		pipe(fd[j]); //on cree le nm de pipe
		j++;
	}

	//pipe(fd);

	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	path = ft_strdup(envp[i]);

	cmds = take_multiple_args(argv, ac, path);
	// while (cmds!= NULL)
	// {
	// 	printf("%s \n", cmds->cmdp);
	// 	cmds = cmds->next;
	// }
	// exit(0);
	// test lst chainees por multipipe
	pid = fork();
	printf ("HEY \n");
	while (cmds != NULL)
	{
		printf("Cooking command [%s] \n", cmds->cmdp);
		printf("en haut \n");
		if (pid == 0)
		{
			printf("1 / PID = %d  (parent : %d)\n", getpid(), getppid());
			printf("CMD TO EXEC = %s \n", cmds->cmdp);
			if (cmds->next !=NULL)
			printf("NEXT CMD TO EXEC = %d - %s \n", cmds->next->index, cmds->next->cmdp);
			dup2(fd[0][1], STDOUT_FILENO); //
			dup2(infile, STDIN_FILENO);	   //test, infile devient le STDIN
			close(fd[0][0]);
			close(fd[0][1]);
			execve(cmds->cmdp, cmds->cmd_args, envp);
		}
		else
		{
			pid2 = fork();
			if (pid2 == 0)
			{
				printf("2 / PID = %d  (parent : %d)\n", getpid(), getppid());
				printf("CMD TO EXEC = %s \n", cmds->cmdp);
				if (cmds->next !=NULL)
				printf("NEXT CMD TO EXEC = %d - %s \n", cmds->next->index, cmds->next->cmdp);
				dup2(fd[1][0], fd[0][1]); // on redirgine STDIN sur reading end u pipe
				dup2(fd[1][1], STDOUT_FILENO);
				close(fd[1][0]);
				close(fd[1][1]);
				execve(cmds->cmdp, cmds->cmd_args, envp);
			}
			else //parent parent, premier a s'exec
			{
				printf("3 / PID = %d  (parent : %d)\n", getpid(), getppid());
				printf("CMD TO EXEC = %s \n", cmds->cmdp);
				if (cmds->next != NULL)
				printf("NEXT CMD TO EXEC = %d - %s \n", cmds->next->index, cmds->next->cmdp);
				dup2(fd[2][0], fd[1][1]);	  // on redirgine STDIN sur reading end u pipe
				dup2(outfile, STDOUT_FILENO); // ici je redirige la sortie de la commande vers outfile
				close(fd[2][0]);
				close(fd[1][1]);
				execve(cmds->cmdp, cmds->cmd_args, envp);
			}
		}
		cmds = cmds->next;
		printf ("_________\n");
		// i = -1;
		while (++i < 2)
		 	wait(&status);
	}
	printf("ici \n");
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][0]);
	close(fd[2][1]);
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
