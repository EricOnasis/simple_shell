#include "shell.h"

/**
 * tokenize_input - get token of string
 * @line: command user
 * Return: To a pointer
 */
char **tokenize_input(char *line)
{
    char **user_command = NULL;
    char *token = NULL;
    size_t i = 0;
    int size = 0;

    if (line == NULL)
        return (NULL);

    for (i = 0; line[i]; i++)
    {
        if (line[i] == ' ')
            size++;
    }
    if ((size + 1) == _strlen(line))
        return (NULL);
    user_command = malloc(sizeof(char *) * (size + 2));
    if (user_command == NULL)
        return (NULL);

    token = _strtok(line, " \n\t\r");
    for (i = 0; token != NULL; i++)
    {
        user_command[i] = token;
        token = _strtok(NULL, " \n\t\r");
    }
    user_command[i] = NULL;
    return (user_command);
}

/**
 * print_env - function to print all environment variables
 * @env: environment
 * Return: 0
 */
void print_env(char **env)
{
    size_t run = 0;

    while (env[run])
    {
        write(STDOUT_FILENO, env[run], _strlen(env[run]));
        write(STDOUT_FILENO, "\n", 1);
        run++;
    }
}

/**
 * get_path - get variable PATH.
 * @env: environment
 * Return: value of PATH.
 */
char *get_path(char **env)
{
    size_t index = 0, var = 0, count = 5;
    char *path = NULL;

    for (index = 0; _strncmp(env[index], "PATH=", 5); index++)
        ;
    if (env[index] == NULL)
        return (NULL);

    for (count = 5; env[index][var]; var++, count++)
        ;
    path = malloc(sizeof(char) * (count + 1));

    if (path == NULL)
        return (NULL);

    for (var = 5, count = 0; env[index][var]; var++, count++)
        path[count] = env[index][var];

    path[count] = '\0';
    return (path);
}


/**
 * find_path - separate the path in new strings.
 * @args: command input of user.
 * @env: environment.
 * Return: a pointer to strings.
 */
int find_path(char **args, char **env)
{
    char *token = NULL, *path_rela = NULL, *path_absol = NULL;
    size_t value_path, command;
    struct stat stat_lineptr;

    if (stat(*args, &stat_lineptr) == 0)
        return (-1);
    path_rela = get_path(env);
    if (!path_rela)
        return (-1);
    token = _strtok(path_rela, ":");
    command = _strlen(*args);
    while (token)
    {
        value_path = _strlen(token);
        path_absol = malloc(sizeof(char) * (value_path + command + 2));
        if (!path_absol)
        {
            free(path_rela);
            return (-1);
        }
        path_absol = _strcpy(path_absol, token);
        _strcat(path_absol, "/");
        _strcat(path_absol, *args);

        if (stat(path_absol, &stat_lineptr) == 0)
        {
            *args = path_absol;
            free(path_rela);
            return (0);
        }
        free(path_absol);
        token = _strtok(NULL, ":");
    }
    free(path_rela);
    return (-1);
}