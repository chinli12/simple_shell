/**
 * str_to_int - converts a string to an integer
 * @str: the string to be converted
 * Return: -1 on error, converted number otherwise
*/
int str_to_int(char *str)
{
	int i, num = 0;

	if (*str == '-')
	{
		/** negative number*/
		return (-1);
	}
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			/** not a number*/
			return (-1);
		}
		num = num * 10 + (str[i] - '0');
	}
	return (num);
}

/**
 * print_err - prints an error message
 * @info: the parameter & return info struct
 * @msg: string containing specified error message
 * Return: none
*/
void print_err(info_t *info, char *msg)
{
	_eputs(info->fname);
	_eputs(": ");
	print_int(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(msg);
}

/**
 * print_int - function prints an integer to a file descriptor
 * @num: the integer to print
 * @fd: the filedescriptor to write to
 * Return: number of characters printed
*/
int print_int(int num, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;

	if (fd == STDERR_FILENO)
	{
		__putchar = _eputchar;
	}
	if (num == 0)
	{
		__putchar('0');
		count++;
	}
	if (num < 0)
	{
		__putchar('-');
		num *= -1;
		count++;
	}
	for (i = 1000000000; i > 0; i /= 10)
	{
		if (num / i != 0)
		{
			__putchar((num / i) + '0');
			count++;
		}
		num %= i;
	}
	return (count);
}

/**
 * to_hex - converts a number to a hexadecimal string
 * @num: number
 * Return: string
*/
char *to_hex(long int num)
{
	static char *hex;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	hex = "0123456789abcdef";
	ptr = &buffer[49];
	*ptr = '\0';


	do	{
		*--ptr = hex[n % 16];
		n /= 16;
	} while (n != 0);

	return (ptr);
}

/**
 * remove_comment - removes a comment from a string
 * @str: string to remove comment from
 * Return: none
*/
void remove_comment(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '#')
		{
			str[i] = '\0';
			break;
		}
	}
}
