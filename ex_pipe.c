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


int main(int argc, char *argv[], char *env[])
{
  pid_t          pid;
  int            status;
  int            pipe_fd[2];

  if (pipe(pipe_fd) == -1)
    {
      perror("pipe");
      return 1;
    }

  if ((pid = fork()) == -1)
    {
      perror("fork");
      return 1;
    }
  else if (pid == 0) //FILS VA ECRIRE
    {
      close(pipe_fd[0]);
      write(pipe_fd[1], "super\0", 6);
      close(pipe_fd[1]);
      return 1;
    }
  else // PID PERE VA LIRE
    {
      char          buffer[1024];
      int           ret;

      close(pipe_fd[1]);
      while ((ret = read(pipe_fd[0], buffer, 1023)))
        {
          buffer[ret] = 0;
          printf("buff - %s\n", buffer);
        }
      close(pipe_fd[0]);
    }

  return 0;
}
