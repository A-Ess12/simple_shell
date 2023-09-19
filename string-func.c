#include "shell.h"

/**
 * customStrlen - Calculate the length of a string.
 * @str: The string whose length to calculate.
 *
 * Return: The length of the string.
 */
int customStrlen(char *str) {
    int length = 0;

    if (!str) {
        return 0;
    }

    while (*str) {
        length++;
        str++;
    }

    return length;
}

/**
 * customStrcmp - Compare two strings lexicographically.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: 0 if str1 is equal to str2, negative if str1 < str2, positive if str1 > str2.
 */
int customStrcmp(char *str1, char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return (*str1 - *str2);
        }
        str1++;
        str2++;
    }

    if (*str1 == *str2) {
        return 0;
    } else {
        return (*str1 < *str2 ? -1 : 1);
    }
}

/**
 * customStartsWith - Check if a string starts with another string.
 * @str: The string to search.
 * @prefix: The prefix to find.
 *
 * Return: Address of the next character of the string if it starts with the prefix, or NULL.
 */
char *customStartsWith(const char *str, const char *prefix) {
    while (*prefix) {
        if (*prefix++ != *str++) {
            return NULL;
        }
    }
    return (char *)str;
}

/**
 * customStrcat - Concatenate two strings.
 * @dest: The destination buffer.
 * @src: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *customStrcat(char *dest, char *src) {
    char *result = dest;

    while (*dest) {
        dest++;
    }

    while (*src) {
        *dest++ = *src++;
    }

    *dest = *src;

    return result;
}
