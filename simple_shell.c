#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define ARGUMENTS_SIZE 64

extern char **environ;

int main(void) {
    char buffer[BUFFER_SIZE];
    char *arguments[ARGUMENTS_SIZE];
    int status = 1;  // Status flag to control the shell loop

    while (status) {
        printf("#cisfun$ ");  // Display the prompt
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break;  // End of file condition (Ctrl+D)
        }

        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline

        char *token = strtok(buffer, " ");
        int argCount = 0;

        while (token != NULL && argCount < ARGUMENTS_SIZE - 1) {
            arguments[argCount] = token;
            token = strtok(NULL, " ");
            argCount++;
        }
        arguments[argCount] = NULL;  // Null-terminate the arguments array

        if (strcmp(arguments[0], "exit") == 0) {
            // Handle exit built-in command
            status = 0;
        } else if (strcmp(arguments[0], "env") == 0) {
            // Handle env built-in command
            char **env = environ;
            while (*env != NULL) {
                printf("%s\n", *env);
                env++;
            }
        } else {
            // Check if the command exists in the PATH
            char *commandPath = NULL;
            char *pathEnv = getenv("PATH");

            if (pathEnv != NULL) {
                char *pathToken = strtok(pathEnv, ":");

                while (pathToken != NULL) {
                    char *tempPath = malloc(strlen(pathToken) + strlen(arguments[0]) + 2);
                    sprintf(tempPath, "%s/%s", pathToken, arguments[0]);

                    if (access(tempPath, X_OK) == 0) {
                        commandPath = tempPath;
                        break;
                    }

                    free(tempPath);
                    pathToken = strtok(NULL, ":");
                }
            }

            pid_t pid = fork();
            if (pid < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Child process
                if (commandPath != NULL) {
                    if (execv(commandPath, arguments) == -1) {
                        perror(commandPath);
                        exit(EXIT_FAILURE);
                    }
                } else {
                    printf("%s: command not found\n", arguments[0]);
                    exit(EXIT_FAILURE);
                }
            } else {
                // Parent process
                int childStatus;
                waitpid(pid, &childStatus, 0);
            }

            free(commandPath);
        }
    }

    return 0;
}

