#include "shell.h"
/**
 * custom_puts - writes a string to a given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int custom_puts(char *str, int fd)
{
	int i = 0, buf_idx = 0;
	char buffer[WRITE_BUF_SIZE];

	if (!str)
		return (0);

	while (str[i] != '\0')
	{
		if (buf_idx >= WRITE_BUF_SIZE - 1)
		{
			write(fd, buffer, buf_idx);
			buf_idx = 0;
		}

		buffer[buf_idx++] = str[i++];
	}

	if (buf_idx > 0)
		write(fd, buffer, buf_idx);

	return (i);
}
