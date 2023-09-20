#include "shell.h"

/**
 * strtow : it splits the  string into words. Repeated delimiters are ignored
 * fiber: the input string
 * b: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *fiber, char *b)
{
	int u, v, x, y, numwords = 0;
	char **z;

	if (fiber == NULL || fiber[0] == 0)
		return (NULL);
	if (!b)
		b = " ";
	for (u = 0; fiber[u] != '\0'; u++)
		if (!is_delim(fiber[u], b) && (is_delim(fiber[u + 1], b) || !fiber[u + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	z = malloc((1 + numwords) * sizeof(char *));
	if (!z)
		return (NULL);
	for (u = 0, v = 0; v < numwords; v++)
	{
		while (is_delim(fiber[u], b))
			u++;
		x = 0;
		while (!is_delim(fiber[u + x], b) && fiber[u + x])
			x++;
		z[v] = malloc((x + 1) * sizeof(char));
		if (!z[v])
		{
			for (x = 0; x < v; x++)
				free(z[x]);
			free(z);
			return (NULL);
		}
		for (y = 0; y < x; y++)
			z[v][y] = fiber[u++];
		z[v][y] = 0;
	}
	z[v] = NULL;
	return (z);
}

/**
 * strtow2: it splits a string into words
 * strss: the input string
 * b: the delimeter
 */
char **strtow2(char *fiber, char b)
{
	int u, v, x, y, numwords = 0;
	char **z;

	if (fiber == NULL || fiber[0] == 0)
		return (NULL);
	for (u = 0; fiber[u] != '\0'; u++)
		if ((fiber[u] != b && fiber[u + 1] == b) ||
		    (fiber[u] != b && !fiber[u + 1]) || fiber[u + 1] == b)
			numwords++;
	if (numwords == 0)
		return (NULL);
	z = malloc((1 + numwords) * sizeof(char *));
	if (!z)
		return (NULL);
	for (u = 0, v = 0; v < numwords; v++)
	{
		while (fiber[u] == b && fiber[u] != b)
			u++;
		x = 0;
		while (fiber[u + x] != b && fiber[u + x] && fiber[u + x] != b)
			x++;
		z[v] = malloc((x + 1) * sizeof(char));
		if (!z[y])
		{
			for (x = 0; x < y; x++)
				free(z[x]);
			free(z);
			return (NULL);
		}
		for (y = 0; y < x; y++)
			z[v][y] = fiber[u++];
		z[v][y] = 0;
	}
	z[v] = NULL;
	return (z);
}
