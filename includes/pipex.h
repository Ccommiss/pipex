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
#include "libft.h"

typedef struct s_cmd t_cmd;

typedef struct s_cmd {
	int		index;
	char	*cmdp; // command path
	char 	**cmd_args; //command args;
	t_cmd	*next;
	t_cmd	*head;

}			t_cmd;

enum {
	INFILE,
	OUTFILE
};

void	free_fds(int **fd, int i, t_cmd *head);
void	error_quit(void);
void	get_file(int file[2], char **argv, int ac);
void	pipe_fds(int ***fd, int pipes);
void find_command(char **cmd, char ***args, char *path);
t_cmd	*take_multiple_args(char **argv, int ac, char **envp);