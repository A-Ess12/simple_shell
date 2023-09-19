#include "shell.h"

/**
 * bufferInput - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t bufferInput(info_t *info, char **buf, size_t *len)
{
	ssize_t bytesRead = 0;
	size_t currentLength = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handleSigint);
#if USE_GETLINE
		bytesRead = getline(buf, &currentLength, stdin);
#else
		bytesRead = customGetline(info, buf, &currentLength);
#endif
		if (bytesRead > 0)
		{
			if ((*buf)[bytesRead - 1] == '\n')
			{
				(*buf)[bytesRead - 1] = '\0'; /* remove trailing newline */
				bytesRead--;
			}
			info->linecount_flag = 1;
			removeComments(*buf);
			buildHistoryList(info, *buf, info->histcount++);
			/* if (strContains(*buf, ';')) is this a command chain? */
			{
				*len = bytesRead;
				info->cmd_buf = buf;
			}
		}
	}
	return bytesRead;
}

/**
 * getInput - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t getInput(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t bytesRead = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	bytesRead = bufferInput(info, &buf, &len);
	if (bytesRead == -1) /* EOF */
		return -1;
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		checkChain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (isChain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return _strlen(p); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from customGetline() */
	return bytesRead; /* return length of buffer from customGetline() */
}

/**
 * readBuffer - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: bytesRead
 */
ssize_t readBuffer(info_t *info, char *buf, size_t *i)
{
	ssize_t bytesRead = 0;

	if (*i)
		return 0;
	bytesRead = read(info->readfd, buf, READ_BUF_SIZE);
	if (bytesRead >= 0)
		*i = bytesRead;
	return bytesRead;
}

/**
 * customGetline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: bytesRead
 */
int customGetline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytesRead = 0, totalBytesRead = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		totalBytesRead = *length;
	if (i == len)
		i = len = 0;

	bytesRead = readBuffer(info, buf, &len);
	if (bytesRead == -1 || (bytesRead == 0 && len == 0))
		return -1;

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, totalBytesRead, totalBytesRead ? totalBytesRead + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (totalBytesRead)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	totalBytesRead += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = totalBytesRead;
	*ptr = p;
	return totalBytesRead;
}

/**
 * handleSigint - blocks ctrl-C
 * @sigNum: the signal number
 *
 * Return: void
 */
void handleSigint(__attribute__((unused))int sigNum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
