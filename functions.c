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
	int exit_status = atoi(args[1]);
	
	if (!args[1])
	{
		free(line);
		free(args);
		exit(status);
	}
	
	free(line);
	free(args);
	exit(exit_status);
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
 * fork_and_execute - function that creates a fork
 * @args: command and values path
 * @av: Has the name of our program
 * @env: environment
 * @line: command line for the user
 * @process_id: id of process
 * @checker: Checker add new test
 * Return: 0 success
 */

int fork_and_execute(char **args, char **av, char **env,
		char *line, int process_id, int checker)
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
