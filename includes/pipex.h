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


# define CMD_ERR "Command not found."
# define EXEC_ERR "Error while trying to exec. Please enter a valid command."
# define MALLOC_ERR "Error while trying to malloc."
# define FORK_ERR "Could not fork."
# define DUP_ERR "Could not dup."
# define USAGE "Usage : ./pipex \"infile\" \"cmd1\" \"cmd2\" ..... \"outfile\""
# define FILE "Could not open provided infile."

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

void	free_fds(int **fd, t_cmd *head);
void	error_quit(char *err, t_cmd *cmd, int **fd);
void	get_file(int file[2], char **argv, int ac);
void	pipe_fds(int ***fd, int pipes);
void	find_command(char **cmd, char ***args, char *path);
t_cmd	*take_multiple_args(char **argv, int ac, char **envp);

size_t   ft_strlen(const char *s);
int                             ft_strncmp(const char *f, const char *s, size_t len);
void                    ft_putendl_fd(char const *s, int fd);
char                    **ft_split(char const *s, char c);
void                    ft_memdel(void **ptr);
void                    ft_putendl(char const *s);
char                    *ft_strconcat(char *s1, char *s2, int size);
char			*ft_strdup(const char *s);
void			ft_free_double_tab(char **tab);
int                             ft_malloc_char_pointer(int size, char **ptr);
void                    *ft_memcpy(void *dst, const void *src, size_t size);
