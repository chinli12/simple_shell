#include "shell.h"

/**
 * display_prompt - Displays the shell prompt
 */
void display_prompt(void)
{
	printf("#cisfun$ ");
}

/**
 * read_command - Reads a command from stdin
 * @command: The buffer to store the command
 */
void read_command(char *command)
{
	if (!fgets(command, MAX_COMMAND_LENGTH, stdin))
	{
		printf("\n");
		exit(EXIT_SUCCESS);
	}

	command[strcspn(command, "\n")] = '\0';
}
