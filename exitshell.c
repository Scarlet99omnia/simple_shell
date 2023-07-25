#include "shell.h"

/**
 * exitshell - exits the shell
 * @info: Structure containing potential arguments.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int exitshell(inft *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = errconvstring(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			printError(info, "Illegal number: ");
			printsinput(info->argv[1]);
			printsinputchar('\n');
			return (1);
		}
		info->errnum = errconvstring(info->argv[1]);
		return (-2);
	}
	info->errnum = -1;
	return (-2);
}

/**
 * cdp - changes the current directory of the process
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int cdp(inft *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		printsInput("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = getvalueEnv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = getvalueEnv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (stringcmp(info->argv[1], "-") == 0)
	{
		if (!getvalueEnv(info, "OLDPWD="))
		{
			printsInput(s);
			_putchar('\n');
			return (1);
		}
		printsInput(getvalueEnv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = getvalueEnv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		printError(info, "can't cd to ");
		printsinput(info->argv[1]), printsinputchar('\n');
	}
	else
	{
		intenv(info, "OLDPWD", getvalueEnv(info, "PWD="));
		intenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * cdhelp - changes the current directory of the process
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int cdhelp(inft *info)
{
	char **arg_array;

	arg_array = info->argv;
	printsInput("help call works. Function not yet implemented \n");
	if (0)
		printsInput(*arg_array); /* temp att_unused workaround */
	return (0);
}

