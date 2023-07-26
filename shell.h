#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>

void exit_command(char **args, char *line, int status);
void print_env(char **env);
int fork_and_execute(char **args, char **av,
		char **env, char *line, int process_id, int checker);
char *get_user_input(void);
char *get_path(char **env);
char **tokenize_input(char *line);
int main(int argc, char **argv, char **env);

char *_strchr(const char *s, int c);
size_t _strspn(const char *s1, const char *s2);
size_t _strcspn(const char *s1, const char *s2);

char *_strtok(char *str, const char *delim);
size_t _strspn(const char *s1, const char *s2);
size_t _strcspn(const char *s1, const char *s2);
char *_strchr(const char *s, int c);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
size_t _strncmp(char *s1, char *s2, size_t n);
char *_strcpy(char *dest, char *src);
int find_path(char **args, char **env);

#endif
