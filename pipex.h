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
#include "./libft/libft.h"
#define _POSIX_SOURCE

typedef struct s_cmd t_cmd;

typedef struct s_cmd {
	int		index;
	char	*cmdp; // command path
	char 	**cmd_args; //command args;
	t_cmd	*next;

}			t_cmd;

typedef struct s_info t_info;

// typedef struct s_info { pas sure
// 	int 		index_max;
// }				t_info;

void find_command(char **cmd, char ***args, char *path);
t_cmd	*take_multiple_args(char **argv, int ac, char *path);