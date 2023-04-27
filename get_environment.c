#include "shell.h"

/**
 * get_environment - returns a copy of the current environment variables
 * @shell: pointer to shell_t struct
 *
 * Return: array of strings representing the current environment variables
 */
char **get_environment(shell_t *shell)
{
	char **env_copy;

	if (!shell->environment || shell->env_changed)
	{
		env_copy = list_to_strings(shell->env_list);
		if (!env_copy)
			return (NULL);
		free_str_array(shell->environment);
		shell->environment = env_copy;
		shell->env_changed = 0;
	}

	return (shell->environment);
}

/**
 * unset_variable - remove an environment variable from the list
 * @shell: pointer to shell_t struct
 * @var: name of the variable to unset
 *
 * Return: 1 if the variable was unset, 0 otherwise
 */
int unset_variable(shell_t *shell, char *var)
{
	list_t *node = shell->env_list;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			shell->env_changed = delete_node_at_index(&(shell->env_list), i);
			node = shell->env_list;
			continue;
		}
		node = node->next;
		i++;
	}
	return (shell->env_changed);
}

/**
 * set_variable - set an environment variable or modify an existing one
 * @shell: pointer to shell_t struct
 * @var: name of the variable to set
 * @value: value to set the variable to
 *
 * Return: 0 on success, 1 on failure
 */
int set_variable(shell_t *shell, char *var, char *value)
{
	char *buf;
	list_t *node;
	char *p;

	if (!var || !value)
		return (1);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = shell->env_list;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			shell->env_changed = 1;
			free(buf);
			return (0);
		}
		node = node->next;
	}

	if (add_node_end(&(shell->env_list), buf, 0) == NULL)
	{
		free(buf);
		return (1);
	}

	shell->env_changed = 1;
	free(buf);
	return (0);
}
