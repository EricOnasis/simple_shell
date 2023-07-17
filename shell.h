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
#include <fcntl.h>

int _putchar(char c);
void _puts(char *str);
int _atoi(char *s);
char *_strdup(char *str);
char *concat_all(char *name, char *sep, char *value);

char **split_string(char *str, const char *delim);
void execute_command(char **args);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);


extern char **environ;

/**
 * struct list_path - Linked list containing PATH directories
 * @dir: directory in path
 * @p: pointer to next node
 */
typedef struct list_path
{
	char *dir;
	struct list_path *p;
} list_path;

typedef void (*builtin_func)(char **);

/**
 * struct builtin_func_table - Mapping of built-in command names to functions
 * @name: name of the built-in command
 * @func: function implementing the built-in command
 */
typedef struct builtin_func_table
{
	char *name;
	builtin_func func;
} builtin_func_table;

void exit_shell(char **args);
void print_environment(char **args);
void set_environment_variable(char **args);
void unset_environment_variable(char **args);
void (*get_builtin_function(char **args))(char **args);

char *_getenv(const char *name);
list_path *add_path_node_end(list_path **head, char *dir);
list_path *create_path_list(char *path);
char *find_executable_path(char *filename, list_path *head);
void free_path_list(list_path *head);

void sig_handler(int sig_num);
void handle_eof(int len, char *buff);
void check_isatty(void);
void free_arguments(char **args);

#endif
