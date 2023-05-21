#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>

/**
 * execute_command - Execute the given command.
 * @command: The command to execute.
 *
 * This function executes the given command in a new process using fork and exec.
 * It waits for the child process to complete before returning.
 */
void execute_command(char *command);

#endif /* SHELL_H */
