#include "shell.h"

/**
 *_strncpy: it copies a string from 1 distination to another
 *dest: the destination of the  string to be copied to
 *src:source of the string
 *n: the amount of characters that should be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int z, k;
	char *f = dest;

	z = 0;
	while (src[z] != '\0' && z < n - 1)
	{
		dest[z] = src[z];
		z++;
	}
	if (z < n)
	{
		k = z;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (f);
}

/**
 *_strncat: it concatenates two strings
 *league: the first string
 *legend: the second string
 *n: the amount of bytes to be max used
 *Return: the concatenated string
 */
char *_strncat(char *league, char *legend, int n)
{
	int z, k;
	char *f = league;

	z = 0;
	k = 0;
	while (league[z] != '\0')
		z++;
	while (legend[k] != '\0' && k < n)
	{
		league[z] = legend[k];
		z++;
		k++;
	}
	if (k < n)
		league[z] = '\0';
	return (f);
}

/**
 *_strchr: it locates the character in a string
 *f:string to be parsed
 *l:character to look for
 *Return: (f) a pointer to the memory area f
 */
char *_strchr(char *f, char l)
{
	do {
		if (*f == l)
			return (f);
	} while (l++ != '\0');

	return (NULL);
}
