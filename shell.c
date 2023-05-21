#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute_command - Execute the given command.
 * @command: The command to execute.
 *
 * This function executes the given command.
 * It waits for the child process to complete before returning.
 */
void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execlp(command, command, NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}
