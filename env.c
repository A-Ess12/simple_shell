#include "shell.h"

/**
 * myenv - prints the current environment
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int myenv(info_t *info)
{
	printEnvironmentList(info->env);
	return (0);
}

/**
 * getenvValue - gets the value of an environment variable
 * @info: Structure containing potential arguments.
 * @name: environment variable name
 *
 * Return: the value of the environment variable or NULL if not found
 */
char *getenvValue(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = startsWith(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * mysetenv - Initialize a new environment variable or modify an existing one
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (setEnvironmentVariable(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetEnvironmentVariable(info, info->argv[i]);

	return (0);
}

/**
 * populateEnvironmentList - populates the environment linked list
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int populateEnvironmentList(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNodeToEnd(&node, environ[i], 0);
	info->env = node;
	return (0);
}
