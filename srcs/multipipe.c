#include "pipex.h"

void	find_path(char **path, char **envp)
{
	int i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	*path = ft_strdup(envp[i]);
}

t_cmd 	*take_multiple_args(char **argv, int ac, char **envp)
{
	int i;
	char *path;
	t_cmd *cmds;
	t_cmd *head;

	i = 1;
	cmds = malloc(sizeof(t_cmd));
	find_path(&path, envp);
	while (i < ac - 2) // on commence a 1, on finit a ac car dernier = nom du file
	{
		if (i == 1)
			head = cmds;
		cmds->index = i;
		cmds->cmdp = ft_strdup(argv[i + 1]);
		find_command(&cmds->cmdp, &cmds->cmd_args, path);
		i++;
		cmds->next = malloc(sizeof(t_cmd));
		if (i < ac - 2)
			cmds = cmds->next;
		else
			cmds->next = NULL; 
	}
	return head;
}