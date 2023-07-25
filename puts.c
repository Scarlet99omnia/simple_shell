#include "shell.h"

/**
 * printsinput - prints an input string
 * @string : the string to be printed
 * Return: Nothing
 */
void printsinput(char *string)
{
	int i = 0;

	if (!string)
		return;
	while (string[i] != '\0')
	{
		printsinputchar(string[i]);
		i++;
	}
}

/**
 * printsinputchar - writes the character c to stderr
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int printsinputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * printsfd - prints the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int printsfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * pifd - prints an input string
 * @string : the string to be printed
 * @fd: the filedescriptor to write to
 * Return: the number of chars put
 */
int pifd(char *string, int fd)
{
	int i = 0;

	if (!string)
		return (0);
	while (*string)
	{
		i += printsfd(*string++, fd);
	}
	return (i);
}

