#include "pipex.h"


t_cmd 	*take_multiple_args(char **argv, int ac, char *path)
{
	int i;
	t_cmd *cmds;
	t_cmd *head;

	i = 1;
	while (i < ac) // on commence a 1, on finit a ac car dernier = nom du file
	{
		cmds = malloc(sizeof(t_cmd));
		if (i == 1)
			head = cmds;
		cmds->index = i;
		cmds->cmdp = ft_strdup(argv[i]);
		find_command(&cmds->cmdp, &cmds->cmd_args, path);
		printf ("Command %i : %s - args = %s\n", i, cmds->cmdp, cmds->cmd_args[1]);
		i++;
		cmds = cmds->next;
	}
	printf ("head Command %i : %s - args = %s\n", head->index, head->cmdp, head->cmd_args[1]);
	cmds = NULL;
	return head;
}