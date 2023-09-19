#include "shell.h"

/**
 * shellExit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: exits with a given exit status
 * (0) if info->argv[0] != "exit"
 */
int shellExit(info_t *info)
{
	int exitStatus;

	if (info->argv[1])  /* If there is an exit argument */
	{
		exitStatus = safeAtoi(info->argv[1]);
		if (exitStatus == -1)
		{
			info->status = 2;
			printError(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->errorNumber = safeAtoi(info->argv[1]);
		return (-2);
	}
	info->errorNumber = -1;
	return (-2);
}

/**
 * shellCd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int shellCd(info_t *info)
{
	char *currentDir, *newDir, buffer[1024];
	int chdirResult;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		newDir = getEnv(info, "HOME=");
		if (!newDir)
			chdirResult = safeChdir((newDir = getEnv(info, "PWD=")) ? newDir : "/");
		else
			chdirResult = safeChdir(newDir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!getEnv(info, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return (1);
		}
		_puts(getEnv(info, "OLDPWD=")), _putchar('\n');
		chdirResult = safeChdir((newDir = getEnv(info, "OLDPWD=")) ? newDir : "/");
	}
	else
		chdirResult = safeChdir(info->argv[1]);

	if (chdirResult == -1)
	{
		printError(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		setEnv(info, "OLDPWD", getEnv(info, "PWD="));
		setEnv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * shellHelp - displays help information
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int shellHelp(info_t *info)
{
	char **argArray;

	argArray = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argArray); /* temp att_unused workaround */
	return (0);
}
