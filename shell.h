#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <signal.h>

int _putchar(char c);
void _puts(char *str);
int _strlen(char *s);
char *_strdup(char *str);
char *concatenate_strings(char *str1, char *str2, char *str3);
char **splitString(char *str, const char *delim);
void executeCommand(char **argv);
void *reallocateArray(void *ptr, unsigned int oldSize, unsigned int newSize);
extern char **environ;

/**
 * struct PathList - Linked list containing PATH directories
 * @dir: directory in path
 * @next: pointer to next node
 */
typedef struct PathList
{
	char *dir;
	struct PathList *next;
} PathList;

char *getEnvironmentVariable(const char *name);
PathList *addNodeEnd(PathList **head, char *str);
PathList *createPathList(char *path);
char *findPathname(char *filename, PathList *head);

/**
 * struct BuiltinCommand - pointer to function with corresponding builtin command
 * @name: builtin command
 * @func: execute the builtin command
 */
typedef struct BuiltinCommand
{
	char *name;
	void (*func)(char **);
} BuiltinCommand;

void (*checkBuiltin(char **argv))(char **argv);
int convertToInt(char *s);
void exitShell(char **argv);
void printEnvironment(char **argv);
void setEnvironmentVariable(char **argv);
void unsetEnvironmentVariable(char **argv);

void freeArgs(char **argv);
void freePathList(PathList *head);

#endif
