#include "shell.h"

/**
 * initInfo - initializes info_t struct
 * @info: struct address
 */
void initInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * populateInfo - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void populateInfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = splitString(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = duplicateString(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replaceAliases(info);
		replaceVariables(info);
	}
}

/**
 * freeInfo - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void freeInfo(info_t *info, int all)
{
	freeStringArray(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmdBuf)
			free(info->arg);
		if (info->envList)
			freeLinkedList(&(info->envList));
		if (info->historyList)
			freeLinkedList(&(info->historyList));
		if (info->aliasList)
			freeLinkedList(&(info->aliasList));
		freeStringArray(info->environ);
		info->environ = NULL;
		freeBuffer((void **)info->cmdBuf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
