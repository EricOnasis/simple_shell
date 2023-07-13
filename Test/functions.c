#include "shell.h"

/**
 * exit_shell - exits the shell
 * @args: array of words of the entered line
 */
void exit_shell(char **args)
{
	int status = 0;

	if (args[1])
	{
		status = _atoi(args[1]);
		if (status <= -1)
			status = 2;
	}

	free_arguments(args);
	exit(status);
}

/**
 * _atoi - converts a string into an integer
 * @s: pointer to a string
 * Return: the integer
 */
int _atoi(char *s)
{
	int i, integer, sign = 1;

	i = 0;
	integer = 0;
	while (!((s[i] >= '0') && (s[i] <= '9')) && (s[i] != '\0'))
	{
		if (s[i] == '-')
		{
			sign = sign * (-1);
		}
		i++;
	}
	while ((s[i] >= '0') && (s[i] <= '9'))
	{
		integer = (integer * 10) + (sign * (s[i] - '0'));
		i++;
	}
	return (integer);
}

/**
 * print_environment - prints the current environment
 * @args: array of arguments
 */
void print_environment(char **args)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
		_puts("\n");
	}

	free_arguments(args);
}

/**
 * set_environment_variable - Initializes a new
 * environment variable, or modify an existing one
 * @args: array of entered words
 */
void set_environment_variable(char **args)
{
	int i, j, k;

	if (!args[1] || !args[2])
	{
		perror(_getenv("_"));
		return;
	}

	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (args[1][j] == environ[i][j])
		{
			while (args[1][j])
			{
				if (args[1][j] != environ[i][j])
					break;

				j++;
			}
			if (args[1][j] == '\0')
			{
				k = 0;
				while (args[2][k])
				{
					environ[i][j + 1 + k] = args[2][k];
					k++;
				}
				environ[i][j + 1 + k] = '\0';
				return;
			}
		}
	}


	int num_vars = 0;

	while (environ[num_vars])
		num_vars++;

	char *new_var = concat_all(args[1], "=", args[2]);

	environ = realloc(environ, (num_vars + 2) * sizeof(char *));
	environ[num_vars] = new_var;
	environ[num_vars + 1] = NULL;

	free_arguments(args);
}

/**
 * unset_environment_variable - Remove an environment variable
 * @args: array of entered words
 */
void unset_environment_variable(char **args)
{
	int i, j;

	if (!args[1])
	{
		perror(_getenv("_"));
		return;
	}

	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (args[1][j] == environ[i][j])
		{
			while (args[1][j])
			{
				if (args[1][j] != environ[i][j])
					break;

				j++;
			}
			if (args[1][j] == '\0')
			{
				free(environ[i]);
				while (environ[i + 1])
				{
					environ[i] = environ[i + 1];
					i++;
				}
				environ = realloc(environ, (i + 1) * sizeof(char *));
				environ[i] = NULL;
				return;
			}
		}
	}

	free_arguments(args);
}
