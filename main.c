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
#define _POSIX_SOURCE

int main (void)
{
	int id = fork();
	int n;
	int status;
	int fd[2];

	printf ("hi from id %d\n", id);
	if (id == 0)
		n = 1;
	else {
		n = 6;
		printf ("id = %d \n", id);
		waitpid(id, &status, 0);
	}
	int i;
	for (i = n; i < n + 5; i++ ){
		printf ("%d ", i);
		fflush(stdout);
	}
	// printf("%d \n", access("testfile", R_OK));
	// printf("%s \n", strerror(errno));

	// printf ("le fd = %d \n", open("testfile", O_WRONLY));
	// printf("%s \n", strerror(errno));
	// printf ("le fd = %d \n", open("lol", O_WRONLY));
	// printf("%s \n", strerror(errno));
	// printf ("unlink \n");
	// printf ("%d \n", unlink("lols"));
	// printf("%s \n", strerror(errno));
	// printf ("%d \n", unlink("lol")); // pour les symlinks 
	// printf("%s \n", strerror(errno));
	//printf ("end \n\n");


	return (0);
}