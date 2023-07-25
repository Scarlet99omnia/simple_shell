#include "shell.h"
/**
* chainDelim - test if current char in buffer is a chain delimeter
* @info: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
* Return: 1 if chain delimeter, 0 otherwise
*/
int chainDelim(inft *info, char *buf, size_t *p)
{
size_t j = *p;
if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
info->cmdBufType = CMD_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
info->cmdBufType = CMD_AND;
}
else if (buf[j] == ';') /* found end of this command */
{
buf[j] = 0; /* replace semicolon with null */
info->cmdBufType = CMD_CHAIN;
}
else
return (0);
*p = j;
return (1);
}
/**
* chainCheck - checks we should continue chaining based on last status
* @info: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
* @i: starting position in buf
* @len: length of buf
* Return: Void
*/
void chainCheck(inft *info, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;
if (info->cmdBufType == CMD_AND)

{
if (info->status)
{
buf[i] = 0;
j = len;
}
}
if (info->cmdBufType == CMD_OR)
{
if (!info->status)
{
buf[i] = 0;
j = len;
}
}
*p = j;
}
/**
* repalceAlias - replaces an aliases in the tokenized string
* @info: the parameter struct
* Return: 1 if replaced, 0 otherwise
*/
int repalceAlias(inft *info)
{
int i;
list_t *node;
char *p;
for (i = 0; i < 10; i++)
{
node = nodestartswith(info->alias, info->argv[0], '=');
if (!node)
return (0);
free(info->argv[0]);
p = strnchar(node->string, '=');
if (!p)
return (0);
p = stringdup(p + 1);
if (!p)
return (0);
info->argv[0] = p;
}
return (1);
}
/**
* repalceVars - replaces vars in the tokenized string
* @info: the parameter struct
* Return: 1 if replaced, 0 otherwise
*/
int repalceVars(inft *info)
{
int i = 0;
list_t *node;
for (i = 0; info->argv[i]; i++)
{
if (info->argv[i][0] != '$' || !info->argv[i][1])
continue;
if (!stringcmp(info->argv[i], "$?"))
{
repalceString(&(info->argv[i]),

stringdup(convertnumber(info->status, 10, 0)));

continue;
}
if (!stringcmp(info->argv[i], "$$"))
{
repalceString(&(info->argv[i]),

stringdup(convertnumber(getpid(), 10, 0)));

continue;
}
node = nodestartswith(info->env, &info->argv[i][1], '=');
if (node)
{
repalceString(&(info->argv[i]),

stringdup(strnchar(node->string, '=') + 1));

continue;
}
repalceString(&info->argv[i], stringdup(""));
}
return (0);
}
/**
* repalceString - replaces string
* @old: address of old string
* @new: new string
* Return: 1 if replaced, 0 otherwise
*/
int repalceString(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}

