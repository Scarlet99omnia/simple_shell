#include "shell.h"

/**
 * printEnv - prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int printEnv(inft *info)
{
	printListString(info->env);
	return (0);
}

/**
 * getvalueEnv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 * Return: the value
 */
char *getvalueEnv(inft *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = startswith(node->string, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * setEnv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int setEnv(inft *info)
{
	if (info->argc != 3)
	{
		printsinput("Incorrect number of arguements\n");
		return (1);
	}
	if (intenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * rmv_env - Remove an environment variable
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int rmv_env(inft *info)
{
	int i;

	if (info->argc == 1)
	{
		printsinput("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		rmenv(info, info->argv[i]);

	return (0);
}

/**
 * popenvlist - populates env linked list
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int popenvlist(inft *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addnodeend(&node, environ[i], 0);
	info->env = node;
	return (0);
}

