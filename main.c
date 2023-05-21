#include "command_utils.h"
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

#define PROMPT "#cisfun$ "

/**
 * main - Entry point of the shell program.
 *
 * Return: 0 on success.
 */
int main(void)
{
	char *command;

	while (1)
	{
		printf("%s", PROMPT);

		command = read_command();

		if (command == NULL)
		{
			break;
		}

		process_command(command);
		free(command);
	}

	return (0);
}
