#include "shell.h"

/**

get_input_buffer - read from stdin and buffer commands

@shell: shell_t struct

@buffer: address of buffer

@buf_len: address of buffer length

Return: bytes read
*/
ssize_t get_input_buffer(shell_t *shell, char **buffer, size_t *buf_len)
{
	ssize_t bytes_read;
	size_t len_p;

	if (*buf_len == 0)
	{
		free(*buffer);
		*buffer = NULL;
	}
	signal(SIGINT, handle_sigint);
	bytes_read = getline(buffer, &len_p, stdin);

	if (bytes_read > 0)
	{
	
		if ((*buffer)[bytes_read - 1] == '\n')
		{
			(*buffer)[bytes_read - 1] = '\0';
			bytes_read--;
		}
		
		shell->line_count++;
		remove_comments(*buffer);
	
		build_history_list(shell, *buffer, shell->history_count++);
	
		if (strchr(*buffer, ';'))
		{
			*buf_len = bytes_read;
			shell->command_buf = buffer;
		}
	}
}

/**

get_next_command - get the next command from the input buffer

@shell: shell_t struct

Return: bytes read
*/

ssize_t get_next_command(shell_t *shell)
{
	static char *buffer;
	static size_t i, j, buf_len;
	ssize_t bytes_read = 0;
	char **arg_ptr = &(shell->args), *p;
	_putchar(BUF_FLUSH);
	bytes_read = get_input_buffer(shell, &buffer, &buf_len);

	if (bytes_read == -1)
	{
		return (-1);
	}
	if (buf_len)
	{
		j = i;
		p = buffer + i;
		check_command_chain(shell, buffer, &j, i, buf_len);
		while (j < buf_len)
		{
			if (is_command_chain(shell, buffer, &j))
			{
				break;
			}
			j++;
		}
		i = j + 1;
		if (i >= buf_len)
		{
			i = buf_len = 0;
			shell->command_buf_type = CMD_NORMAL;
		}
		*arg_ptr = p;
		return (strlen(p));
	}
	*arg_ptr = buffer;
	return (bytes_read);
}

/**

read_buffer - read from the readfd and buffer the data

@shell: shell_t struct

@buf: buffer

@len: buffer length

Return: bytes read
*/
ssize_t read_buffer(shell_t *shell, char *buf, size_t *len)
{
	ssize_t bytes_read = 0;

	if (*len)
	{
		return (0);
	}
	bytes_read = read(shell->readfd, buf, READ_BUF_SIZE);
	if (bytes_read >= 0)
	{
		*len = bytes_read;
	}
	return (bytes_read);
}

/**
 * get_line - reads the next line of input from STDIN
 * @info: parameter struct
 * @buffer: address of pointer to buffer, preallocated or NULL
 * @bufsize: size of preallocated buffer if not NULL
 *
 * Return: length of the string read
 */
int get_line(info_t *info, char **buffer, size_t *bufsize)
{
	static char input_buffer[READ_BUF_SIZE];
	static size_t buffer_pos = 0, buffer_len = 0;
	size_t newline_pos;
	ssize_t bytes_read = 0, total_bytes_read = 0;
	char *old_buffer = NULL, *new_buffer = NULL, *newline;

	old_buffer = *buffer;

	if (old_buffer && bufsize)
		total_bytes_read = *bufsize;

	if (buffer_pos == buffer_len)
		buffer_pos = buffer_len = 0;

	bytes_read = read_buffer(info, input_buffer, &buffer_len);
	if (bytes_read == -1 || (bytes_read == 0 && buffer_len == 0))
		return (-1);

	newline = _strchr(input_buffer + buffer_pos, '\n');
	newline_pos = newline ? 1 + (unsigned int)(newline - input_buffer) : buffer_len;

	new_buffer = _realloc(old_buffer, total_bytes_read, (total_bytes_read ? total_bytes_read + newline_pos : newline_pos + 1));
	if (!new_buffer) /** MALLOC FAILURE! */
		return (old_buffer ? free(old_buffer), -1 : -1);

	if (total_bytes_read)
		_strncat(new_buffer, input_buffer + buffer_pos, newline_pos - buffer_pos);
	else
		_strncpy(new_buffer, input_buffer + buffer_pos, newline_pos - buffer_pos + 1);

	total_bytes_read += newline_pos - buffer_pos;
	buffer_pos = newline_pos;
	*buffer = new_buffer;

	if (bufsize)
		*bufsize = total_bytes_read;

	return (total_bytes_read);
}

/**
 * sigint_handler - blocks SIGINT
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigint_handler(__attribute__((unused))int sig_num)
{
	_puts("\n$ ");
	_putchar(BUF_FLUSH);
}

