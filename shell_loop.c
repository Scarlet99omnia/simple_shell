#include "shell.h"
/**
* msh - main shell loop
* info: the parameter & return info struct
* av: the argument vector from main()
* Return: 0 on success, 1 on error, or error code
*/
int msh(inft *info, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;
while (r != -1 && builtin_ret != -2)
{
clearInfo(info);
if (interact(info))
printsInput("$ ");
printsinputchar(BUF_FLUSH);
r = getinput(info);
if (r != -1)
{
intInfo(info, av);
builtin_ret = findBuiltinCmd(info);
if (builtin_ret == -1)
find_cmd(info);
}
else if (interact(info))
_putchar('\n');
freeInfo(info, 0);
}
writehistory(info);
freeInfo(info, 1);
if (!interact(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->errnum == -1)
exit(info->status);
exit(info->errnum);
}
return (builtin_ret);
}
/**
* findBuiltinCmd : finds a builtin command
* info: the parameter and return info struct
* Return: -1 if builtin not found,
* 0 if builtin executed successfully,
* 1 if builtin found but not successful,
* 2 if builtin signals exit()
*/
int findBuiltinCmd(inft *info)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", exitshell},
{"env", printEnv},
{"help", cdhelp},
{"history", dispHist},
{"setEnv", setEnv},
{« set_env", rmv_env},
{"cd", cdp},
{"alias", builtAlias},
{NULL, NULL}
};
for (i = 0; builtintbl[i].type; i++)
if (stringcmp(info->argv[0], builtintbl[i].type) == 0)
{
info->errcount++;
built_in_ret = builtintbl[i].func(info);
break;
}
return (built_in_ret);
}
/**
* find_cmd - finds a command in PATH
* @info: the parameter & return info struct
*
* Return: void
*/
void find_cmd(inft *info)
{
char *path = NULL;
int i, k;
info->path = info->argv[0];
if (info->linecountflag == 1)

{
info->errcount++;
info->linecountflag = 0;
}
for (i = 0, k = 0; info->arg[i]; i++)
if (!checkdelim(info->arg[i], " \t\n"))
k++;
if (!k)
return;
path = findCmdPath(info, getvalueEnv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
forkcmd(info);
}
else
{
if ((interact(info) || getvalueEnv(info, "PATH=")
|| info->argv[0][0] == '/') && excmd(info, info->argv[0]))
forkcmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
printError(info, "not found\n");
}
}
}
/**
* forkcmd : forks a an exec thread to run cmd
* info: the parameter and return info struct
* Return: void
*/
void forkcmd(inft *info)
{
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->argv, returnenviron(info)) == -1)
{
freeInfo(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
/* TODO: PUT ERROR FUNCTION */
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
printError(info, "Permission denied\n");
}
}
}
