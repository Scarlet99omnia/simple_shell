#include "shell.h"
/**
* stringcp - copies a string
* @dest: the destination
* @src: the source
*
* Return: pointer to destination
*/
char *stringcp(char *dest, char *src)
{
int i = 0;
if (dest == src || src == 0)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}
/**
* stringdup - duplicates a string
* @string the string to duplicate
*
* Return: pointer to the duplicated string
*/
char *stringdup(const char *string
{
int length = 0;
char *ret;
if (string == NULL)
return (NULL);
while (*string++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}
/**
* printsInput - prints an input string
* @string the string to be printed
*
* Return: Nothing
*/
void printsInput(char *string
{
int i = 0;
if (!str)
return;
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}
/**
* _putchar - writes the character c to stdout
* @c: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}
