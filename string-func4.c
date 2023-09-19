#include "shell.h"

/**
 * customStrSplit - Split a string into words using delimiters.
 * @inputStr: The input string.
 * @delimiters: The delimiter characters.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **customStrSplit(char *inputStr, const char *delimiters) {
    int i, j, k, m, numWords = 0;
    char **result;

    if (inputStr == NULL || inputStr[0] == '\0') {
        return NULL;
    }

    if (!delimiters) {
        delimiters = " ";
    }

    for (i = 0; inputStr[i] != '\0'; i++) {
        if (!isDelimiter(inputStr[i], delimiters) &&
            (isDelimiter(inputStr[i + 1], delimiters) || !inputStr[i + 1])) {
            numWords++;
        }
    }

    if (numWords == 0) {
        return NULL;
    }

    result = malloc((1 + numWords) * sizeof(char *));
    if (!result) {
        return NULL;
    }

    for (i = 0, j = 0; j < numWords; j++) {
        while (isDelimiter(inputStr[i], delimiters)) {
            i++;
        }

        k = 0;
        while (!isDelimiter(inputStr[i + k], delimiters) && inputStr[i + k]) {
            k++;
        }

        result[j] = malloc((k + 1) * sizeof(char));
        if (!result[j]) {
            for (k = 0; k < j; k++) {
                free(result[k]);
            }
            free(result);
            return NULL;
        }

        for (m = 0; m < k; m++) {
            result[j][m] = inputStr[i++];
        }
        result[j][m] = '\0';
    }

    result[j] = NULL;
    return result;
}
