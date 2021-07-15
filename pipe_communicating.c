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
	printf ("%s\n", argv[ac - 1]);
	int outfile = open(argv[ac - 1], O_RDWR);
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
		printf ("on malloc %d\n", j);
		fd[j] = malloc(sizeof(int) * 2);
		fd[j][0] = 9;
		printf ("fd j 0 = %d \n", fd[j][0]);
		j++;
	}

	while (j < ac - 4)
	{
		pipe(fd[j]); //on cree le nm de pipe
		printf ("on pipe j = %d\n", j);
		j++;
	}

	j = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	path = ft_strdup(envp[i]);

	cmds = take_multiple_args(argv, ac, path);
	
	
	//test, infile devient le STDIN
	
	i = 0; 
	while (cmds != NULL)
	{	
		printf ("FD = %d \n", i);
		sleep(1);
		pid = fork();
		printf ("PROCESS = %d\n", pid);
		sleep(1);
		printf("Cooking command [%s] \n", cmds->cmdp);
		printf("en haut \n");
		if (pid == 0)
		{
			printf("1 / PID = %d  (parent : %d)\n", getpid(), getppid());
			printf("CMD TO EXEC = %s \n", cmds->cmdp);
			sleep(1);
			if (i == 0)
				dup2(infile, STDIN_FILENO);
			if (i >= 1){
				printf ("passe par la \n");
				dup2(fd[i - 1][0], STDIN_FILENO);
			}
			sleep(1);
			dup2(fd[i - 1][1], STDOUT_FILENO);

			sleep(1);
			if (i < ac - 4)
			{
				printf (" i = %d \n", i);
				dup2(fd[i][1], STDOUT_FILENO);
			}
			if (i == ac - 4) //last command
			{
				puts("on rentre \n");
				dup2(outfile, STDOUT_FILENO);
			}
			close(fd[i - 1][0]);
			close(fd[i - 1][1]);
			close(fd[i][0]);
			close(fd[i][1]);
			execve(cmds->cmdp, cmds->cmd_args, envp);
			printf ("yo\n");
		}
		// else //parent stuff 
		// {
		// 		// printf("3 / PID = %d  (parent : %d)\n", getpid(), getppid());
		// 		// printf("CMD TO EXEC = %s \n", cmds->cmdp);
		// 		// printf ("FD = %d\n", i);
		// 		// dup2(fd[i][0], STDIN_FILENO); // on redirgine STDIN sur reading end u pipe
		// 		// dup2(outfile, STDOUT_FILENO); 
		// 		// close(fd[i][0]);
		// 		// close(fd[i][1]);
		// 		//execve(cmds->cmdp, cmds->cmd_args, envp);
		// }
	
		cmds = cmds->next;
		printf ("_________\n");
		i++;
	}
	printf("ici \n");
	// close(fd[0][0]);
	// close(fd[0][1]);
	// close(fd[1][0]);
	// close(fd[1][1]);
	waitpid(pid, NULL, 0);
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
