#include "shell.h"

/**
 * main - main arguments functions
 * @argc: count of arguments
 * @argv: arguments
 * @env: environment
 * Return: _exit = 0.
 */
int main(int argc, char **argv, char **env)
{
    char *getcommand = NULL, **user_command = NULL;
    int pathValue = 0, _exit = 0, n = 0;
    (void)argc;

    while (1)
    {
        getcommand = get_user_input();
        if (getcommand)
        {
            pathValue++;
            user_command = tokenize_input(getcommand);
            if (!user_command)
            {
                free(getcommand);
                continue;
            }
            if ((!_strcmp(user_command[0], "exit")) && user_command[1] == NULL)
                exit_command(user_command, getcommand, _exit);
            if (!_strcmp(user_command[0], "env"))
                print_env(env);
            else
            {
                n = find_path(user_command, env);
                _exit = fork_and_execute(user_command, argv, env, getcommand, pathValue, n);
                if (n == 0)
                    free(user_command[0]);
            }
            free(user_command);
        }
        else
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            exit(_exit);
        }
        free(getcommand);
    }
    return (_exit);
}