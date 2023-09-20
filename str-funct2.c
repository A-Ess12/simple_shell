#include "shell.h"

/**
 * _strcpy:it copies a string
 * dest:destination
 * src:source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int z = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[z])
	{
		dest[z] = src[z];
		z++;
	}
	dest[z] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * str: the string we want to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *_puts - prints an input string
 *str: the string that should be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int z = 0;

	if (!str)
		return;
	while (str[z] != '\0')
	{
		_putchar(str[z]);
		z++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * p: The character to be printed
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char p)
{
	static int z;
	static char buf[WRITE_BUF_SIZE];

	if (p == BUF_FLUSH || z >= WRITE_BUF_SIZE)
	{
		write(1, buf, z);
		z = 0;
	}
	if (p != BUF_FLUSH)
		buf[z++] = p;
	return (1);
}
