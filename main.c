#include <unistd.h>
#include <stdio.h> 
#include <string.h>
#include <errno.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (void)
{
	printf("%d \n", access("testfile", R_OK));
	printf("%s \n", strerror(errno));

	printf ("le fd = %d \n", open("testfile", O_WRONLY));
	printf("%s \n", strerror(errno));
	printf ("le fd = %d \n", open("lol", O_WRONLY));
	printf("%s \n", strerror(errno));
	printf ("unlink \n");
	printf ("%d \n", unlink("lols"));
	printf("%s \n", strerror(errno));
	printf ("%d \n", unlink("lol")); // pour les symlinks 
	printf("%s \n", strerror(errno));


	return (0);
}