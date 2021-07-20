#include "pipex.h"

void	find_command(char **cmd, char ***args, char *path)
{
	int		j;
	char	**tab;
	char	*command_path;

	j = -1;
	*args = ft_split(*cmd, ' ');
	tab = ft_split(path, ':');
	while (tab[++j] != NULL)
	{
		path = ft_strconcat(tab[j], "/", ft_strlen(tab[j]) + 1);
		command_path = ft_strconcat(path, args[0][0],
				ft_strlen(path) + ft_strlen(args[0][0]));
		if (access(command_path, F_OK) == 0)
		{
			*cmd = ft_strdup(command_path);
			break ;
		}
	}
}

void	find_path(char **path, char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	*path = ft_strdup(envp[i]);
}

t_cmd	*take_multiple_args(char **argv, int ac, char **envp)
{
	int		i;
	char	*path;
	t_cmd	*cmds;
	t_cmd	*head;

	i = 1;
	cmds = malloc(sizeof(t_cmd));
	find_path(&path, envp);
	while (i < ac - 2)
	{
		if (i == 1)
			head = cmds;
		cmds->index = i - 1;
		cmds->head = head;
		cmds->cmdp = ft_strdup(argv[i + 1]);
		find_command(&cmds->cmdp, &cmds->cmd_args, path);
		i++;
		cmds->next = malloc(sizeof(t_cmd));
		if (i < ac - 2)
			cmds = cmds->next;
		else
			cmds->next = NULL;
	}
	return (head);
}
