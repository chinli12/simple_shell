/**
 * display_history - prints out the command history with line numbers
 * @info: structure containing command history
 *
 * Return: Always 0
 */
int display_history(info_t *info)
{
	list_t *node = info->history;
	int count = 0;

	while (node)
	{
		printf("%d %s\n", count++, node->str);
		node = node->next;
	}

	return (0);
}

/**
 * unset_alias_cmd - removes an alias command
 * @info: parameter struct
 * @cmd: the alias command to remove
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias_cmd(info_t *info, char *cmd)
{
	char *p, c;
	int ret;

	p = strchr(cmd, '=');
	if (!p)
		return (1);

	c = *p;
	*p = '\0';
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, cmd, -1)));
	*p = c;

	return (ret);
}

/**
 * set_alias_cmd - sets an alias command
 * @info: parameter struct
 * @cmd: the alias command
 *
 * Return: 0 on success, 1 on error
 */
int set_alias_cmd(info_t *info, char *cmd)
{
	char *p;

	p = strchr(cmd, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias_cmd(info, cmd));

	unset_alias_cmd(info, cmd);
	return (add_node_end(&(info->alias), cmd, 0) == NULL);
}

/**
 * print_alias_cmd - prints an alias command
 * @node: the alias node
 *
 * Return: 0 on success, 1 on error
 */
int print_alias_cmd(list_t *node)
{
	char *p = NULL, *alias_cmd = NULL;

	if (node)
	{
		p = strchr(node->str, '=');
		for (alias_cmd = node->str; alias_cmd <= p; alias_cmd++)
			putchar(*alias_cmd);
		putchar('\'');
		puts(p + 1);
		return (0);
	}
	return (1);
}

/**
 * alias_cmd - manages alias commands
 * @info: parameter struct
 *
 * Return: Always 0
 */
int alias_cmd(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias_cmd(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = strchr(info->argv[i], '=');
		if (p)
			set_alias_cmd(info, info->argv[i]);
		else
			print_alias_cmd(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

