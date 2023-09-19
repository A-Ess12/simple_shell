#include "shell.h"

/**
 * safeAtoi - converts a string to an integer with error handling
 * @s: the string to be converted
 *
 * Return: Converted integer if successful, -1 on error
 */
int safeAtoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++; 

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printErrorMessage - prints an error message with information
 * @info: the info struct
 * @errorMessage: string containing specified error type
 */
void printErrorMessage(info_t *info, char *errorMessage)
{
	_eputs(info->fname);
	_eputs(": ");
	printInteger(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(errorMessage);
}

/**
 * printInteger - prints an integer to the specified file descriptor
 * @input: the integer to print
 * @fd: the file descriptor to write to
 *
 * Return: Number of characters printed
 */
int printInteger(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int absValue, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		absValue = -input;
		__putchar('-');
		count++;
	}
	else
		absValue = input;
	current = absValue;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absValue / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convertToBase - converts a number to a specified base
 * @num: number to convert
 * @base: base to convert to
 * @flags: argument flags
 *
 * Return: string representation of the converted number
 */
char *convertToBase(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * removeFirstComment - replaces the first '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0
 */
void removeFirstComment(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
