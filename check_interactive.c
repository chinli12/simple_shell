#include "helper.h"

/**
 * check_interactive - returns true if shell is in interactive mode
 * @input_fd: file descriptor of the input stream
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int check_interactive(int input_fd)
{
	if (isatty(input_fd) && input_fd <= STDERR_FILENO)
		return (1);
	return (0);
}

/**
 * is_delimiter - checks if character is a delimiter
 * @ch: the character to check
 * @delimiter: the delimiter string
 *
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char ch, char *delimiter)
{
	int i = 0;

	while (delimiter[i])
	{
		if (delimiter[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

/**
 * is_alphabetic - checks for alphabetic character
 * @ch: The character to check
 *
 * Return: 1 if ch is alphabetic, 0 otherwise
 */
int is_alphabetic(char ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		return (1);
	return (0);
}

/**
 * str_to_int - converts a string to an integer
 * @str: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */
int str_to_int(char *str)
{
	int i = 0, sign = 1, output = 0;
	unsigned int result = 0;

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}

	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + (str[i] - '0');
		}
		else
			break;
		i++;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
