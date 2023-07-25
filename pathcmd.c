#include "shell.h"
/**
* excmd - determines if a file is an executable command
* @info: the info struct
* @path: path to the file
* Return: 1 if true, 0 otherwise
*/
int excmd(inft *info, char *path)
{
struct stat st;
(void)info;
if (!path || stat(path, &st))
return (0);
if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}
/**
* dupChars - duplicates characters
* @pathstring : the PATH string
* @start: starting index
* @stop: stopping index
* Return: pointer to new buffer
*/
char *dupChars(char *pathstring, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;
for (k = 0, i = start; i < stop; i++)
if (pathstring[i] != ':')
buf[k++] = pathstring[i];
buf[k] = 0;
return (buf);
}
/**
* findCmdPath - finds this cmd in the PATH string
* @info: the info struct
* @pathstring: the PATH string
* @cmd: the cmd to be finded
* Return: full path of cmd if found or NULL
*/
char *findCmdPath(inft *info, char *pathstring, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;
if (!pathstring)
return (NULL);
if ((strlength(cmd) > 2) && startswith(cmd, "./"))
{
if (excmd(info, cmd))
return (cmd);
}
while (1)
{
if (!pathstring[i] || pathstring[i] == ':')
{
path = dupChars(pathstring, curr_pos, i);
if (!*path)
stringcat(path, cmd);
else
{
stringcat(path, "/");
stringcat(path, cmd);
}
if (excmd(info, path))
return (path);
if (!pathstring[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}
