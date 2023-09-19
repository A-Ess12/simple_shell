#include "shell.h"

/**
 **_memoryFill - fills memory with a constant byte
 *@dest: the pointer to the memory area
 *@value: the byte to fill *dest with
 *@size: the number of bytes to fill
 *Return: (dest) a pointer to the memory area dest
 */
char *_memoryFill(char *dest, char value, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		dest[i] = value;
	return (dest);
}

/**
 * freeStringArray - frees an array of strings
 * @strArray: array of strings to free
 */
void freeStringArray(char **strArray)
{
	char **temp = strArray;

	if (!strArray)
		return;
	while (*strArray)
		free(*strArray++);
	free(temp);
}

/**
 * customRealloc - reallocates a memory block with enhanced functionality
 * @prevBlock: pointer to the previous memory block
 * @oldSize: size of the previous block in bytes
 * @newSize: size of the new block in bytes
 *
 * Return: pointer to the reallocated memory block
 */
void *customRealloc(void *prevBlock, unsigned int oldSize, unsigned int newSize)
{
	char *newBlock;

	if (!prevBlock)
		return (malloc(newSize));
	if (!newSize)
	{
		free(prevBlock);
		return (NULL);
	}
	if (newSize == oldSize)
		return (prevBlock);

	newBlock = malloc(newSize);
	if (!newBlock)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		newBlock[oldSize] = ((char *)prevBlock)[oldSize];
	free(prevBlock);
	return (newBlock);
}
