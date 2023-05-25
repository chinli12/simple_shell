#include "shell.h"

extern char **environ;

/**
 * main - Entry point of the shell program
 * Return: 0 on success
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	display_prompt();

	while (1)
	{
		read_command(command);

		if (is_exit_command(command))
			break;
		else if (strcmp(command, "env") == 0)
			print_environment(environ);
		else
			execute_command(command);

		display_prompt();
	}

	return (0);
}
