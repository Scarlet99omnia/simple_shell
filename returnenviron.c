#include "shell.h"

/**
 * returnenviron - returns the string array copy of our environ
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
char **returnenviron(inft *info)
{
	if (!info->environ || info->envchang)
	{
		info->environ = listToStrings(info->env);
		info->envchang = 0;
	}

	return (info->environ);
}

/**
 * rmenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int rmenv(inft *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = startswith(node->string, var);
		if (p && *p == '=')
		{
			info->envchang = rmvNodeAtIndex(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->envchang);
}

/**
 * intenv - Initialize a new environment variable,
 *              or modify an existing one
 * @info: Structure containing potential arguments.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int intenv(inft *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	but = malloc(strlength(var) + strlength(value) + 2);
	if (!buf)
		return (1);
	stringcp(buf, var);
	stringcat(buf, "=");
	stringcat(buf, value);
	node = info->env;
	while (node)
	{
		p = startswith(node->string, var);
		if (p && *p == '=')
		{
			free(node->string);
			node->string = buf;
			info->envchang = 1;
			return (0);
		}
		node = node->next;
	}
	addnodeend(&(info->env), buf, 0);
	free(buf);
	info->envchang = 1;
	return (0);
}

