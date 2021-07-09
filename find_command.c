#include "pipex.h"

//int main(int ac, char **argv, char **envp)
void find_command(char **cmd, char ***args, char *path)
{
	// on aura ensuite format execve(cmd, args, envp)
	int i;
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
		printf("tested path %s \n", command_path);
		if (access(command_path, F_OK) == 0)
		{
			printf("path = %s \n", command_path);
			*cmd = ft_strdup(command_path);
			break;
		}
	}

	// while (ft_strncmp(envp[i], "PATH", 4) != 0)
	// 	i++;
	// tab = ft_split(envp[i], ':');

	// char **args1;
	// char **args2;
	// char *command_path;

	// recup la commande
	// j = -1;
	// args1 = ft_split(argv[2], ' ');
	// while (args1[++j] != NULL)
	// 	printf("args %s \n", args1[j]);

	// j = -1;
	// args2 = ft_split(argv[3], ' ');
	// while (args2[++j] != NULL)
	// 	printf("args %s \n", args2[j]);

	// // on recup les paths possibles
	// i = 0;
	// while (ft_strncmp(envp[i], "PATH", 4) != 0)
	// 	i++;
	// tab = ft_split(envp[i], ':');
	// j = -1;

	// while (tab[++j] != NULL)
	// 	printf("%s \n", tab[j]);

	// i = -1;
	// j = -1;

	// char *path;
	// while (tab[++j] != NULL)
	// {
	// path = ft_strconcat(tab[j], "/", ft_strlen(tab[j]) + 1);
	// command_path = ft_strconcat(path, args1[0], ft_strlen(path) + ft_strlen(args[0]) );
	// printf ("tested path %s \n", command_path);
	// if (access(command_path, F_OK ) == 0 )
	// {
	// 	printf ("path = %s \n", command_path);
	// 	break;
	// }
	// }

	// execve(command_path, args, envp);
}
