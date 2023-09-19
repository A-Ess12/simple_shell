#include "shell.h"

/**
 * customStrncpy - Copy a string with a specified maximum length.
 * @destination: The destination buffer.
 * @source: The source string.
 * @max_length: The maximum number of characters to copy.
 *
 * Return: Pointer to the destination buffer.
 */
char *customStrncpy(char *destination, const char *source, int max_length) {
    int i = 0;
    char *result = destination;

    while (source[i] != '\0' && i < max_length - 1) {
        destination[i] = source[i];
        i++;
    }

    if (i < max_length) {
        int j = i;
        while (j < max_length) {
            destination[j] = '\0';
            j++;
        }
    }

    return result;
}

/**
 * customStrncat - Concatenate two strings with a specified maximum length.
 * @destination: The first string.
 * @source: The second string.
 * @max_length: The maximum number of characters to concatenate.
 *
 * Return: Pointer to the concatenated string.
 */
char *customStrncat(char *destination, const char *source, int max_length) {
    int i = 0;
    int j = 0;
    char *result = destination;

    while (destination[i] != '\0') {
        i++;
    }

    while (source[j] != '\0' && j < max_length) {
        destination[i] = source[j];
        i++;
        j++;
    }

    if (j < max_length) {
        destination[i] = '\0';
    }

    return result;
}

/**
 * customStrchr - Locate a character in a string.
 * @str: The string to search.
 * @c: The character to look for.
 *
 * Return: Pointer to the first occurrence of the character in the string or NULL if not found.
 */
char *customStrchr(char *str, char c) {
    do {
        if (*str == c) {
            return str;
        }
    } while (*str++ != '\0');

    return NULL;
}
