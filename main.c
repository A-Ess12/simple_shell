#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int custom_fd = 2;

	// Some unique inline assembly
	asm volatile (
		"movl %1, %0\n\t"
		"addl $3, %0"
		: "=r" (custom_fd)
		: "r" (custom_fd)
	);

	if (argc == 2)
	{
		custom_fd = open(argv[1], O_RDONLY);
		if (custom_fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = custom_fd;
	}

	populate_env_list(info);
	read_history(info);
	hsh(info, argv);
	return (EXIT_SUCCESS);
}