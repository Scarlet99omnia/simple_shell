#include "shell.h"
/**
* addnode - adds a node to the start of the list
* @head: address of pointer to head node
* @string :string of node
* @num: node index used by history
* Return: size of list
*/
list_t *addnode(list_t **head, const char *string, int num)
{
list_t *new_head;
if (!head)
return (NULL);
new_head = malloc(sizeof(list_t));
if (!new_head)
return (NULL);
setMemory((void *)new_head, 0, sizeof(list_t));
new_head->num = num;
if (string)
{
new_head->string = stringdup(string);
if (!new_head->string)
{
free(new_head);
return (NULL);
}
}
new_head->next = *head;
*head = new_head;
return (new_head);
}
/**
* addnodeend - adds a node to the end of the list
* @head: address of pointer to head node
* @string : stringfield of node
* @num: node index used by history
* Return: size of list
*/
list_t *addnodeend(list_t **head, const char *string, int num)
{
list_t *new_node, *node;
if (!head)
return (NULL);

node = *head;
new_node = malloc(sizeof(list_t));
if (!new_node)
return (NULL);
setMemory((void *)new_node, 0, sizeof(list_t));
new_node->num = num;
if (string)
{
new_node->string = stringdup(string);
if (!new_node->string)
{
free(new_node);
return (NULL);
}
}
if (node)
{
while (node->next)
node = node->next;
node->next = new_node;
}
else
*head = new_node;
return (new_node);
}
/**
* printListString - prints only the stringelement of a list_t linked list
* @h: pointer to first node
* Return: size of list
*/
size_t printListString(const list_t *h)
{
size_t i = 0;
while (h)
{
printsInput(h->string ? h->string : "(nil)");
printsInput("\n");
h = h->next;
i++;
}
return (i);
}
/**
* rmvNodeAtIndex - deletes node at given index
* @head: address of pointer to first node
* @index: index of node to delete
* Return: 1 on success, 0 on failure
*/
int rmvNodeAtIndex(list_t **head, unsigned int index)
{
list_t *node, *prev_node;
unsigned int i = 0;
if (!head || !*head)
return (0);
if (!index)
{
node = *head;
*head = (*head)->next;
free(node->string);
free(node);
return (1);
}
node = *head;
while (node)
{
if (i == index)
{
prev_node->next = node->next;
free(node->string);
free(node);
return (1);
}
i++;
prev_node = node;
node = node->next;
}
return (0);
}
/**
* freeList - frees all nodes of a list
* @headPtr: address of pointer to head node
* Return: void
*/
void freeList(list_t **headPtr)
{
list_t *node, *next_node, *head;
if (!headPtr || !*headPtr)
return;
head = *headPtr;
node = head;
while (node)
{
next_node = node->next;
free(node->string);
free(node);
node = next_node;
}
*headPtr = NULL;
}
