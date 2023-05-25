#include "shell.h"

/**
 * print_environment - Prints the current environment variables
 * @environ: The array of environment variables
 */
void print_environment(char **environ)
{
	int i = 0;
	char *env = environ[i];

	while (env != NULL)
	{
		printf("%s\n", env);
		env = environ[++i];
	}
}
