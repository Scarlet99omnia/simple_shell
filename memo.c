#include "shell.h"
/**
* setMemory - fills memory with a constant byte
* @s: the pointer to the memory area
* @b: the byte to fill *s with
* @n: the amount of bytes to be filled
* Return: (s) a pointer to the memory area s
*/
char *setMemory(char *s, char b, unsigned int n)
{
unsigned int i;
for (i = 0; i < n; i++)
s[i] = b;
return (s);
}
/**
* freesStrings - frees a string of strings
* @sS: string of Strings
*/
void freesStrings(char **sS)
{
char **a = sS;
if (!sS)
return;
while (*sS)
free(*sS++);
free(a);
}
/**
* reaBlcMem - reallocates a block of memory
* @ptr: pointer to previous malloc'ated block
* @prevSize: byte size of previous block
* @newSize: byte size of new block
* Return: pointer to the all block nameen.
*/
void *reaBlcMem(void *ptr, unsigned int prevSize, unsigned int newSize)
{
char *p;
if (!ptr)
return (malloc(newSize));
if (!newSize)
return (free(ptr), NULL);
if (newSize == prevSize)
return (ptr);
p = malloc(newSize);
if (!p)
return (NULL);
prevSize = prevSize < newSize ? prevSize : newSize;
while (prevSize--)
p[prevSize] = ((char *)ptr)[prevSize];
free(ptr);
return (p);
}
