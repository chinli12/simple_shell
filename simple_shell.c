#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64

/**
 * display_prompt - Display the shell prompt
 */
void display_prompt(void);

/**
 * read_command - Read the user's command from the standard input
 * @command: Buffer to store the command
 */
void read_command(char *command);

/**
 * execute_command - Execute the given command
 * @command: Command to be executed
 */
void execute_command(char *command);

/**
 * is_exit_command - Check if the command is the exit command
 * @command: Command to check
 * Return: 1 if the command is exit, 0 otherwise
 */
int is_exit_command(char *command);

/**
 * print_environment - Print the current environment variables
 */
void print_environment(void);

/**
 * main - Entry point of the shell program
 *
 * Return: 0 on success
 */
int main(void)
{
	display_prompt();
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		read_command(command);

		if (is_exit_command(command))
			break;
		else if (strcmp(command, "env") == 0)
			print_environment();
		else
			execute_command(command);

		display_prompt();
	}

	return (0);
}

/**
 * display_prompt - Display the shell prompt
 */
void display_prompt(void)
{
	printf("#cisfun$ ");
}

/**
 * read_command - Read the user's command from the standard input
 * @command: Buffer to store the command
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

/**
 * execute_command - Execute the given command
 * @command: Command to be executed
 */
void execute_command(char *command)
{
	char *arguments[MAX_ARGUMENTS];
	char *token;
	int arg_index = 0;

	token = strtok(command, " ");
	while (token != NULL && arg_index < MAX_ARGUMENTS - 1)
	{
		arguments[arg_index] = token;
		arg_index++;
		token = strtok(NULL, " ");
	}
	arguments[arg_index] = NULL;

	pid_t pid = fork();

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
		int status;

		if (waitpid(pid, &status, 0) == -1)
		{
			perror("Waitpid failed");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * is_exit_command - Check if the command is the exit command
 * @command: Command to check
 * Return: 1 if the command is exit, 0 otherwise
 */
int is_exit_command(char *command)
{
	return (strcmp(command, "exit") == 0);
}

/**
 * print_environment - Print the current environment variables
 */
void print_environment(void)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
