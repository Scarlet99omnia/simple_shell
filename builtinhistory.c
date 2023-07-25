#include "shell.h"

/**
 * dispHist - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int dispHist(inft *info)
{
	printListT(info->history);
	return (0);
}

/**
 * setAlias - sets alias to string
 * @info: parameter struct
 * @string : the string alias
 * Return: Always 0 on success, 1 on error
 */
int setAlias(inft *info, char *string)
{
	char *p, c;
	int ret;

	p = strnchar(string, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = rmvNodeAtIndex(&(info->alias),
	getNodeIndex(info->alias, nodestartswith(info->alias, string, -1)));
	*p = c;
	return (ret);
}

/**
 * set_Alias - sets alias to string
 * @info: parameter struct
 * @string : the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_Alias(inft *info, char *string)
{
	char *p;

	p = strnchar(string, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (setAlias(info, string));

	setAlias(info, string);
	return (addnodeend(&(info->alias), string, 0) == NULL);
}

/**
 * printAlias - prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int printAlias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = strnchar(node->string, '=');
		for (a = node->string; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		printsInput(p + 1);
		printsInput("'\n");
		return (0);
	}
	return (1);
}

/**
 * builtAlias - mimics the alias builtin
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int builtAlias(inft *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = strnchar(info->argv[i], '=');
		if (p)
			set_Alias(info, info->argv[i]);
		else
			printAlias(nodestartswith(info->alias, info->argv[i], '='));
	}

	return (0);
}

