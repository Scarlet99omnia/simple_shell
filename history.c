#include "shell.h"
/**
* gethistoryfile - gets the history file
* @info: parameter struct
* Return: allocated string containg history file
*/
char *gethistoryfile(inft *info)
{
char *buf, *dir;
dir = getvalueEnv(info, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (strlength(dir) + strlength(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
stringcp(buf, dir);
stringcat(buf, "/");
stringcat(buf, HIST_FILE);
return (buf);
}
/**
* writehistory - creates a file, or appends to an existing file
* @info: the parameter struct
* Return: 1 on success, else -1
*/
int writehistory(inft *info)
{
ssize_t fd;
char *filename = gethistoryfile(info);
list_t *node = NULL;
if (!filename)
return (-1);
fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = info->history; node; node = node->next)
{
pifd(node->string, fd);
printsfd('\n', fd);
}
printsfd(BUF_FLUSH, fd);
close(fd);
return (1);
}
/**
* readhistory - reads history from file
* @info: the parameter struct
* Return: histcount on success, 0 otherwise
*/
int readhistory(inft *info)
{
int i, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = gethistoryfile(info);
if (!filename)
return (0);
fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
buildhistlist(info, buf + last, linecount++);
last = i + 1;
}
if (last != i)
buildhistlist(info, buf + last, linecount++);
free(buf);
info->histcount = linecount;
while (info->histcount-- >= HIST_MAX)
rmvNodeAtIndex(&(info->history), 0);
renumbHist(info);
return (info->histcount);
}
/**
* buildhistlist - adds entry to a history linked list
* @info: Structure containing potential arguments. Used to maintain
* @buf: buffer
* @linecount: the history linecount, histcount
* Return: Always 0
*/
int buildhistlist(inft *info, char *buf, int linecount)
{
list_t *node = NULL;
if (info->history)
node = info->history;
addnodeend(&node, buf, linecount);
if (!info->history)
info->history = node;
return (0);
}
/**
* renumbHist - renumbers the history linked list after changes
* @info: Structure containing potential arguments.
* Return: the new histcount
*/
int renumbHist(inft *info)
{
list_t *node = info->history;
int i = 0;
while (node)
{
node->num = i++;
node = node->next;
}
return (info->histcount = i);
}
