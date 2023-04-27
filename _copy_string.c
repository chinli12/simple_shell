#include "shell.h"

/**
 * _copy_string - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 *
 * Return: the concatenated string
 */
char *_copy_string(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * _concat_strings - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 *
 * Return: the concatenated string
 */
char *_concat_strings(char *dest, char *src, int n)
{
	int i = 0, dest_len = 0;

	while (dest[dest_len] != '\0')
	{
		dest_len++;
	}

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[dest_len + i] = src[i];
	}

	dest[dest_len + i] = '\0';

	return (dest);
}

/**
 * _find_char - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 *
 * Return: a pointer to the first occurrence of the char or NULL if not found
 */
char *_find_char(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}

		s++;
	}

	return (NULL);
}
