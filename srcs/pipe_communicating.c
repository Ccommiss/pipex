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

/*
**	Redirects stdin on read ends of fds, or infile if first command
**	Redirects stdout on write ends of fds, or outfile if last command
*/
void	dup_ends(t_cmd *cmds, int infile, int outfile, int **fd)
{
	if (cmds->index == 0)
	{
		if (dup2(infile, STDIN_FILENO) == -1)
			error_quit();
	}
	else if (cmds->index != 0)
	{
		if (dup2(fd[cmds->index - 1][0], STDIN_FILENO) < 0)
			error_quit();
		close(fd[cmds->index - 1][1]);
		close(fd[cmds->index - 1][0]);
	}
	if (cmds->next == NULL)
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
			error_quit();
	}
	else if (cmds->next != NULL)
	{
		close(fd[cmds->index][0]);
		if (dup2(fd[cmds->index][1], STDOUT_FILENO) == -1)
			error_quit();
		close(fd[cmds->index][1]);
	}
}

/*
**	Parent is closing fds
*/
void	close_fds(int **fd, t_cmd *cmds)
{
	close(fd[cmds->index - 1][1]);
	close(fd[cmds->index - 1][0]);
}

void	free_fds(int **fd, t_cmd *head)
{
	int pipes;
	t_cmd *tmp;

	pipes = 0;
	while (head != NULL)
	{
		tmp = head;
		free(head->cmdp); // command path
		ft_free_double_tab(head->cmd_args);
		head = head->next;
		if (tmp->index > pipes)
			pipes = tmp->index;
		dprintf (2, "index = %d path = %s \n", tmp->index, tmp->cmdp);
		free(tmp);
	}

	while(pipes-- > 0)
		free(fd[pipes]);
	free(fd);
	dprintf (2, "OK POUR FDS \n");
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
int	main(int ac, char **argv, char **envp)
{
	int		files[2];
	int		**fd;
	pid_t	pid;
	t_cmd	*cmds;
	t_cmd   *head;

	get_file(files, argv, ac);
	pipe_fds(&fd, ac - 4);
	cmds = take_multiple_args(argv, ac, envp);
	head = cmds;
	while (cmds != NULL)
	{
		pid = fork();
		if (pid == -1)
			error_quit();
		if (pid == 0)
		{
			dup_ends(cmds, files[INFILE], files[OUTFILE], fd);
			if (execve(cmds->cmdp, cmds->cmd_args, envp) == -1)
				error_quit();
		}
		if (cmds->index >= 1)
			close_fds(fd, cmds);
		cmds = cmds->next;
	}
	free_fds(fd, head);
	return (1);
}
