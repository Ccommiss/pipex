while (command)
{
	pid = fork();
	if (pid == 0)
	{
		/* child gets input from the previous command,
            if it's not the first command */
		if (not first command)
		{
			if (dup2(pipefds[(commandc - 1) * 2], 0) <)
			{
				perror and exit
			}
		}
		/* child outputs to next command, if it's not
            the last command */
		if (not last command)
		{
			if (dup2(pipefds[commandc * 2 + 1], 1) < 0)
			{
				perror and exit
			}
		}
		close all pipe - fds
							 execvp
								 perror and exit
	}
	else if (pid < 0){
		perror and exit} cmd = cmd->next
								   commandc++
}