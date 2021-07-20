#include "pipex.h"

void find_command(char **cmd, char ***args, char *path)
{
	int j;
	char **tab;

	j = -1;
	*args = ft_split(*cmd, ' '); // fini
	tab = ft_split(path, ':');

	char *command_path;
	while (tab[++j] != NULL)
	{
		path = ft_strconcat(tab[j], "/", ft_strlen(tab[j]) + 1);
		command_path = ft_strconcat(path, args[0][0], ft_strlen(path) + ft_strlen(args[0][0]));
		if (access(command_path, F_OK) == 0)
		{
			*cmd = ft_strdup(command_path);
			break;
		}
	}
}
