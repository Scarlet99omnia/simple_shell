#include "shell.h"

/**
 * clearInfo - initializes inft struct
 * @info: struct address
 */
void clearInfo(inft *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * intInfo - initializes inft struct
 * @info: struct address
 * @av: argument vector
 */
void intInfo(inft *info, char **av)
{
	int i = 0;

	info->filename = av[0];
	if (info->arg)
	{
		info->argv = stringtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = stringdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		repalceAlias(info);
		repalceVars(info);
	}
}

/**
 * freeInfo - frees inft struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void freeInfo(inft *info, int all)
{
	freesStrings(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmdBuf)
			free(info->arg);
		if (info->env)
			freeList(&(info->env));
		if (info->history)
			freeList(&(info->history));
		if (info->alias)
			freeList(&(info->alias));
		freesStrings(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmdBuf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

