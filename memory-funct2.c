#include "shell.h"

/**
 * freeAndNullPointer - frees a pointer and sets it to NULL
 * @ptr: address of the pointer to free and nullify
 *
 * Return: 1 if freed and nullified, otherwise 0.
 */
int freeAndNullPointer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
