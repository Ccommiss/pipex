#include "pipex.h"


t_cmd 	*take_multiple_args(char **argv, int ac, char *path)
{
	int i;
	t_cmd *cmds;
	t_cmd *head;

	i = 1;
	cmds = malloc(sizeof(t_cmd)); 
	while (i < ac - 2) // on commence a 1, on finit a ac car dernier = nom du file
	{
		if (i == 1)
			head = cmds;
		cmds->index = i;
		cmds->cmdp = ft_strdup(argv[i + 1]);
		find_command(&cmds->cmdp, &cmds->cmd_args, path);
		printf ("Command %i : %s - args = %s\n", i, cmds->cmdp, cmds->cmd_args[1]);
		i++;
		cmds->next = malloc(sizeof(t_cmd));
		if (i < ac - 2)
			cmds = cmds->next;
		else
			cmds->next = NULL; 
	}
	printf ("head Command %i : %s - args = %s\n", head->index, head->cmdp, head->cmd_args[1]);
	//cmds = NULL;
	return head;
}