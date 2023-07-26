#include "shell.h"


/**
 * exit_command - this function closes the simple_shell when
 * @args: pointer with the direction argument.
 * @line: standard input string
 * @status: value of exit
 * Return: None
 */
void exit_command(char **args, char *line, int status)
{
    int exit_status = 0;

    if (!args[1])
    {
        free(line);
        free(args);
        exit(status);
    }
    exit_status = atoi(args[1]);

    free(line);
    free(args);
    exit(exit_status);
}

/**
 * fork_and_execute - function that creates a fork
 * @args: command and values path
 * @av: Has the name of our program
 * @env: environment
 * @line: command line for the user
 * @process_id: id of process
 * @checker: Checker add new test
 * Return: 0 success
 */
int fork_and_execute(char **args, char **av, char **env, char *line, int process_id, int checker)
{
    pid_t child;
    int status;
    char *format = "%s: %d: %s: not found\n";

    child = fork();

    if (child == 0)
    {
        if (execve(args[0], args, env) == -1)
        {
            fprintf(stderr, format, av[0], process_id, args[0]);
            if (!checker)
                free(args[0]);
            free(args);
            free(line);
            exit(errno);
        }
    }
    else
    {
        wait(&status);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            return (WEXITSTATUS(status));
    }
    return (0);
}

/**
 * get_user_input - print "#cisfun$ " and wait for the user to type something.
 * Return: line of string input for the user
 */
char *get_user_input(void)
{
    char *line = NULL;
    size_t user_input_size = 0;

    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "$ ", 2);

    if (getline(&line, &user_input_size, stdin) == -1)
    {
        free(line);
        return (NULL);
    }

    return (line);
}
