#include "shell.h"

/**
 * isExecutableCommand - Determines if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int isExecutableCommand(info_t *info, char *path)
{
    struct stat st;

    (void)info;
    if (!path || stat(path, &st))
        return 0;

    if (st.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

/**
 * duplicateCharacters - Duplicates characters from a string within a specified range.
 * @pathStr: The source string.
 * @start: Starting index.
 * @stop: Stopping index.
 *
 * Return: Pointer to a new buffer containing the duplicated characters.
 */
char *duplicateCharacters(char *pathStr, int start, int stop)
{
    static char buffer[1024];
    int i = 0, k = 0;

    for (k = 0, i = start; i < stop; i++)
    {
        if (pathStr[i] != ':')
        {
            buffer[k++] = pathStr[i];
        }
    }

    buffer[k] = '\0';
    return buffer;
}

/**
 * findCommandPath - Finds the full path of a command in the PATH string.
 * @info: The info struct.
 * @pathStr: The PATH string.
 * @command: The command to find.
 *
 * Return: Full path of the command if found, or NULL if not found.
 */
char *findCommandPath(info_t *info, char *pathStr, char *command)
{
    int i = 0, currPos = 0;
    char *path;

    if (!pathStr)
        return NULL;

    if ((_strlen(command) > 2) && startsWith(command, "./"))
    {
        if (isExecutableCommand(info, command))
            return command;
    }

    while (1)
    {
        if (!pathStr[i] || pathStr[i] == ':')
        {
            path = duplicateCharacters(pathStr, currPos, i);
            if (!*path)
                strcat(path, command);
            else
            {
                strcat(path, "/");
                strcat(path, command);
            }
            if (isExecutableCommand(info, path))
                return path;

            if (!pathStr[i])
                break;

            currPos = i;
        }
        i++;
    }

    return NULL;
}
