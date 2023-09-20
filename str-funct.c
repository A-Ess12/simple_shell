#include "shell.h"

/**
 * _strlen: it  returns the length of a string
 * @t: the string whose length has to be checked
 *
 * Return- integer length of string
 */
int _strlen(char *t)
{
	int i = 0;

	if (!t)
		return (0);

	while (*t++)
		i++;
	return (i);
}

/**
 * _strcmp - it  performs  comparison of two strings.
 * @t1: the first string
 * @t2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *t1, char *t2)
{
	while (*t1 && *t2)
	{
		if (*t1 != *t2)
			return (*t1 - *t2);
		t1++;
		t2++;
	}
	if (*t1 == *t2)
		return (0);
	else
		return (*t1 < *t2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
