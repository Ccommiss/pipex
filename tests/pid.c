 #include <sys/wait.h>
       #include <stdlib.h>
       #include <unistd.h>
       #include <stdio.h>

       int
       main(int argc, char *argv[])
       {
           pid_t cpid, w;
           int status;

           cpid = fork();
           if (cpid == -1) {
               perror("fork");
               exit(EXIT_FAILURE);
           }

           if (cpid == 0) {            /* Code exécuté par le fils */
               printf("Le PID du fils est %ld\n", (long) getpid());
               if (argc == 1)
                   pause();                    /* Attendre un signal */
               _exit(atoi(argv[1]));

           } else {                    /* Code exécuté par le père */
               do {
                   w = waitpid(cpid, &status, WUNTRACED | WCONTINUED);
                   if (w == -1) {
                       perror("waitpid");
                       exit(EXIT_FAILURE);
                   }

                   if (WIFEXITED(status)) {
                       printf("terminé, code=%d\n", WEXITSTATUS(status));
                   } else if (WIFSIGNALED(status)) {
                       printf("tué par le signal %d\n", WTERMSIG(status));
                   } else if (WIFSTOPPED(status)) {
                       printf("arrêté par le signal %d\n", WSTOPSIG(status));
                   } else if (WIFCONTINUED(status)) {
                       printf("relancé\n");
                   }
               } while (!WIFEXITED(status) && !WIFSIGNALED(status));
               exit(EXIT_SUCCESS);
           }
       }
