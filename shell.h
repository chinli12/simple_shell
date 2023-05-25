#ifndef SHELL_H
#define SHELL_H

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
void print_environment(char **environ);

#endif /* SHELL_H */
