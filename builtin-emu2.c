#include "shell.h"

/**
 * shellHistory - displays the command history with line numbers
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int shellHistory(info_t *info)
{
	printListWithNumbers(info->history);
	return (0);
}

/**
 * unsetShellAlias - unsets a shell alias
 * @info: parameter struct
 * @str: the alias string
 *
 * Return: 0 on success, 1 on error
 */
int unsetShellAlias(info_t *info, char *str)
{
	char *equals, temp;

	equals = _strchr(str, '=');
	if (!equals)
		return (1);

	temp = *equals;
	*equals = '\0';
	int ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, nodeStartsWith(info->alias, str, -1)));
	*equals = temp;

	return (ret);
}

/**
 * setShellAlias - sets a shell alias
 * @info: parameter struct
 * @str: the alias string
 *
 * Return: 0 on success, 1 on error
 */
int setShellAlias(info_t *info, char *str)
{
	char *equals = _strchr(str, '=');
	if (!equals)
		return (1);

	if (!*++equals)
		return (unsetShellAlias(info, str));

	unsetShellAlias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * printShellAlias - prints a shell alias
 * @node: the alias node
 *
 * Return: 0 on success, 1 on error
 */
int printShellAlias(list_t *node)
{
	char *equals = NULL, *alias = NULL;

	if (node)
	{
		equals = _strchr(node->str, '=');
		for (alias = node->str; alias <= equals; alias++)
			_putchar(*alias);
		_putchar('\'');
		_puts(equals + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * shellAlias - handles shell aliases
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int shellAlias(info_t *info)
{
	int i = 0;
	char *equals = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			printShellAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equals = _strchr(info->argv[i], '=');
		if (equals)
			setShellAlias(info, info->argv[i]);
		else
			printShellAlias(nodeStartsWith(info->alias, info->argv[i], '='));
	}

	return (0);
}
