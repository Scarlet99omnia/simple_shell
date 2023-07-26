#include "shell.h"

/**
 * inputbuf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t inputbuf(inft *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmdBuf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = getsline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecountflag = 1;
			rmvComments(*buf);
			buildhistlist(info, *buf, info->histcount++);
			/* if (stringchar(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmdBuf = buf;
			}
		}
	}
	return (r);
}

/**
 * getinput - gets a line minus the newline
 * @info: parameter struct
 * Return: bytes read
 */
ssize_t getinput(inft *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = inputbuf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		chainCheck(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (chainDelim(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmdBufType = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (strlength(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from getsline() */
	return (r); /* return length of buffer from getline() */
}

/**
 * readbuf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 * Return: r
 */
ssize_t readbuf(inft *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READBUFSIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * getsline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int getsline(inft *info, char **ptr, size_t *length)
{
	static char buf[READBUFSIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = readbuf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = strnchar(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = reaBlcMem(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		strncat(new_p, buf + i, k - i);
	else
		stringcpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @signalnum: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int signalnum)
{
	printsInput("\n");
	printsInput("$ ");
	_putchar(BUF_FLUSH);
}

