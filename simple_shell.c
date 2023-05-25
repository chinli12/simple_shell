#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64

void display_prompt(void);
void read_command(char *command);
void execute_command(char *command);
int is_exit_command(char *command);
void print_environment(void);

/**
 * @main: the main application that runs
 * */
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
			print_environment();
		else
			execute_command(command);

		display_prompt();
	}

	return (0);
}

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

/**
 * print_environment - Prints the current environment variables
 */
void print_environment(void)
{
	char **environ;
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
