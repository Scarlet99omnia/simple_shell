#include "shell.h"
/**
* listlength - determines length of linked list
* @h: pointer to first node
* Return: size of list
*/
size_t listlength(const list_t *h)
{
size_t i = 0;
while (h)
{
h = h->next;
i++;
}
return (i);
}
/**
* listToStrings - returns an array of strings of the list->string
* @head: pointer to first node
* Return: array of strings
*/
char **listToStrings(list_t *head)
{
list_t *node = head;
size_t i = listlength(head), j;
char **strs;
char *string;
if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
string = malloc(strlength(node->string) + 1);
if (!string)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}
string = stringcp(string, node->string);
strs[i] = string;
}
strs[i] = NULL;
return (strs);
}

/**
* printListT - prints all elements of a list_t linked list
* @h: pointer to first node
* Return: size of list
*/
size_t printListT(const list_t *h)
{
size_t i = 0;
while (h)
{
printsInput(convertnumber(h->num, 10, 0));
_putchar(':');
_putchar(' ');
printsInput(h->string ? h->string : "(nil)");
printsInput("\n");
h = h->next;
i++;
}
return (i);
}
/**
* nodestartswith - returns node whose string starts with prefix
* @node: pointer to list head
* @prefix: string to match
* @c: the next character after prefix to match
* Return: match node or null
*/
list_t *nodestartswith(list_t *node, char *prefix, char c)
{
char *p = NULL;
while (node)
{
p = startswith(node->string, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}
/**
* getNodeIndex - gets the index of a node
* @head: pointer to list head
* @node: pointer to the node
* Return: index of node or -1
*/
ssize_t getNodeIndex(list_t *head, list_t *node)
{
size_t i = 0;
while (head)
{
if (head == node)
return (i);
head = head->next;
i++;
}
return (-1);
}
