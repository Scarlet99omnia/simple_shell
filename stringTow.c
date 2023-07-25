#include "shell.h"
/**
* **stringtow - splits a string into words. Repeat delimiters are ignored
* @string : the input string
* @d: the delimeter string
* Return: a pointer to an array of strings, or NULL on failure
*/
char **stringtow(char *string, char *d)
{
int i, j, k, m, numwords = 0;
char **s;
if (string == NULL || string[0] == 0)
return (NULL);
if (!d)
d = " ";
for (i = 0; string[i] != '\0'; i++)
if (!checkdlm(string[i], d) && (checkdlm(string[i + 1], d) || !string[i + 1]))
numwords++;
if (numwords == 0)
return (NULL);
s = malloc((1 + numwords) *sizeof(char *));
if (!s)
return (NULL);
for (i = 0, j = 0; j < numwords; j++)
{
while (checkdlm(string[i], d))
i++;
k = 0;
while (!checkdlm(string[i + k], d) && string[i + k])
k++;
s[j] = malloc((k + 1) * sizeof(char));
if (!s[j])
{
for (k = 0; k < j; k++)
free(s[k]);
free(s);
return (NULL);
}
for (m = 0; m < k; m++)
s[j][m] = string[i++];
s[j][m] = 0;
}
s[j] = NULL;
return (s);
}
/**
* **stringtow2 - splits a string into words
* @string: the input string
* @d: the delimeter
* Return: a pointer to an array of strings, or NULL on failure
*/
char **stringtow2(char *string, char d)
{
int i, j, k, m, numwords = 0;
char **s;
if (string == NULL || string[0] == 0)
return (NULL);
for (i = 0; string[i] != '\0'; i++)
if ((string[i] != d && string[i + 1] == d) ||
(string[i] != d && !string[i + 1]) || string[i + 1] == d)
numwords++;
if (numwords == 0)
return (NULL);
s = malloc((1 + numwords) *sizeof(char *));
if (!s)
return (NULL);
for (i = 0, j = 0; j < numwords; j++)
{
while (string[i] == d && string[i] != d)
i++;
k = 0;
while (string[i + k] != d && string[i + k] && string[i + k] != d)
k++;
s[j] = malloc((k + 1) * sizeof(char));
if (!s[j])
{
for (k = 0; k < j; k++)
free(s[k]);
free(s);
return (NULL);
}
for (m = 0; m < k; m++)
s[j][m] = string[i++];
s[j][m] = 0;
}
s[j] = NULL;
return (s);
}
