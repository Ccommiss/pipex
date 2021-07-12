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
#define _POSIX_SOURCE

int main(int ac, char **argv, char **envp)
{
	int fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();

	int infile = open("./infile", O_RDWR);
	int outfile = open("./outfile", O_RDWR);

	
	if (pid == 0)
	{
		char buffer[100];
		// close(fd[0]);
		// write(fd[1], "Child sends\n", 13);
		dup2(infile, STDOUT_FILENO); // va fermer STDOUT (1) puis l'ouvrir le fichier infile donc "redirige" 1 vers infile ;
							// stdout est notre file 
		close(infile);
		close(fd[1]);
		read(fd[0], buffer, sizeof(buffer));
		printf ("Child reads : %s\n", buffer);
		printf ("Try to printf in child \n");
		close(fd[0]);
	}
	else
	{
		//char buffer[100];
		// close(fd[1]);
		// read(fd[0], buffer, sizeof(buffer));
		// printf ("Parent receive : %s\n", buffer);
		close(fd[0]);
		write(fd[1], "parent sends\n", 13);
		printf ("Try to printf in aprent \n");
		close(fd[1]);
	}
}