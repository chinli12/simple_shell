#ifndef COMMAND_UTILS_H
#define COMMAND_UTILS_H

/**
 * read_command - Read user input from stdin.
 *
 * This function reads a line of input from the user via stdin.
 * It allocates memory for the command and returns a pointer to the buffer.
 *
 * Return: Pointer to the allocated buffer containing the command,
 *         or NULL if the end of file is reached.
 */
char *read_command(void);

/**
 * process_command - Process the user command.
 * @command: The command to process.
 *
 * This function processes the user command based on its contents.
 * If the command is "exit", the program will terminate.
 * If the command is "env", it will print the current environment variables.
 * Otherwise, it will execute the command.
 */
void process_command(char *command);

#endif /* COMMAND_UTILS_H */
