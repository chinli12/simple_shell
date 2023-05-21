#include "command_utils.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100
#define PROMPT "#cisfun$ "

/**
 * read_command - Read user input from stdin.
 *
 * Return: Pointer to the allocated buffer containing the command,
 *         or NULL if the end of file is reached.
 */
char *read_command(void)
{
	char *command = malloc(MAX_COMMAND_LENGTH * sizeof(char));

	if (command == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		return (NULL);

	command[strcspn(command, "\n")] = '\0';

	return (command);
}


/**
 * process_command - Process the given command.
 * @command: The command to process.
 *
 * It handles any errors that occur during command processing.
 */
void process_command(char *command)
{
	if (strcmp(command, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(command, "env") == 0)
	{
		char **environ;

		for (char **env = environ; *env != NULL; env++)
			printf("%s\n", *env);
	}
	else
	{
		execute_command(command);
	}
}
