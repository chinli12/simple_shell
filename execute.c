#include "shell.h"

/**
 * execute_command - Executes a command
 * @command: The command to execute
 */
void execute_command(char *command)
{
	char *arguments[MAX_ARGUMENTS];
	char *token;
	int arg_index = 0;
	pid_t pid;
	int status;

	token = strtok(command, " ");
	while (token != NULL && arg_index < MAX_ARGUMENTS - 1)
	{
		arguments[arg_index] = token;
		arg_index++;
		token = strtok(NULL, " ");
	}
	arguments[arg_index] = NULL;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execvp(arguments[0], arguments) == -1)
		{
			perror("Command execution failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Waitpid failed");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * is_exit_command - Checks if a command is the exit command
 * @command: The command to check
 * Return: 1 if it is the exit command, 0 otherwise
 */
int is_exit_command(char *command)
{
	return (strcmp(command, "exit") == 0);
}
