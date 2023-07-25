#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* read/write buffers */
#define READBUFSIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct listsin - singly linked list
 * @num: the number field
 * @string: a string
 * @next: points to the next node
 */
typedef struct listsin
{
	int num;
	char *string;
	struct listsin *next;
} list_t;

/**
 * struct passinfu - contains pseudo-arguements to pass into a function,
 *                  allowing uniform prototype for function pointer struct
 * @arg : a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @errcount: the error count
 * @errnum: the error code for exit()s
 * @linecountflag: if on count this line of input
 * @filename: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @envchang: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmdBuf: address of pointer to cmdBuf, on if chaining
 * @cmdBufType: CMD-type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfu
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int errcount;
	int errnum;
	int linecountflag;
	char *filename;
	list_t *env;
	list_t *history;
	list_t *alias;

	char **environ;
	int envchang;
	int status;
	char **cmdBuf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmdBufType; /* CMD-type ||, &&, ; */
	int readfd;
	int histcount;
} inft;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(inft *);
} builtin_table;


/* shelloop.c */
int msh(inft *, char **);
int findBuiltinCmd(inft *);
void find_cmd(inft *);
void forkcmd(inft *);

/* pathcmd */
int excmd(inft *, char *);
char *dupChars(char *, int, int);
char *findCmdPath(inft *, char *, char *);

/* loopmsh.c */
int loopmsh(char **);

/* puts.c */
void printsinput(char *);
int printsinputchar(char);
int printsfd(char c, int fd);
int pifd(char *string, int fd);

/* string.c */
int strlength(char *);
int stringcmp(char *, char *);
char *startswith(const char *, const char *);
char *stringcat(char *, char *);

/* stringSet.c */
char *stringcp(char *, char *);
char *stringdup(const char *);
void printsInput(char *);
int _putchar(char);

/* stringSet1.c */
char *stringcpy(char *, char *, int);
char *stringcat(char *, char *, int);
char *stringchar(char *, char);

/* stringTow.c */
char **stringtow(char *, char *);
char **stringtow2(char *, char);

/* memo.c */
char *setMemory(char *, char, unsigned int);
void freesStrings(char **);
void *reaBlcMem(void *, unsigned int, unsigned int);

/* pointer.c */
int bfree(void **);

/* convstring.c */
int interact(inft *);
int checkdelim(char, char *);
int checkalpha(int);
int convstring(char *);

/* errors.c */
int errconvstring(char *);
void printError(inft *, char *);
int printdec(int, int);
char *convertnumber(long int, int, int);
void rmvComments(char *);

/* exitshell.c */
int exitshell(inft *);
int cdp(inft *);
int cdhelp(inft *);

/* builtinhistory.c */
int dispHist(inft *);
int builtAlias(inft *);

/* getsLine.c */
ssize_t getinput(inft *);
int getsline(inft *, char **, size_t *);
void sigintHandler(int);

/* information.c */
void clearInfo(inft *);
void intInfo(inft *, char **);
void freeInfo(inft *, int);

/* environ.c */
char *getvalueEnv(inft *, const char *);
int printEnv(inft *);
int setEnv(inft *);
int rmv_env(inft *);
int popenvlist(inft *);

/* returnenviron.c */
char **returnenviron(inft *);
int rmenv(inft *, char *);
int intenv(inft *, char *, char *);

/* history.c */
char *gethistoryfile(inft *info);
int writehistory(inft *info);
int readhistory(inft *info);
int buildhistlis(inft *info, char *buf, int linecount);
int renumbHist(inft *info);

/* node.c */
list_t *addnode(list_t **, const char *, int);
list_t *addnodeend(list_t **, const char *, int);
size_t printListString(const list_t *);
int rmvNodeAtIndex(list_t **, unsigned int);
void freeList(list_t **);

/* lists.c */
size_t listlength(const list_t *);
char **listToStrings(list_t *);
size_t printListT(const list_t *);
list_t *nodestartswith(list_t *, char *, char);
ssize_t getNodeIndex(list_t *, list_t *);

/* chain.c */
int chainDelim(inft *, char *, size_t *);
void chainCheck(inft *, char *, size_t *, size_t, size_t);
int repalceAlias(inft *);
int repalceVars(inft *);
int repalceString(char **, char *);

#endif

