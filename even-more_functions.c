#include "shell.h"

/**
 * printEnvironment - prints the current environment
 * @argv: array of arguments
 */
void printEnvironment(char **argv __attribute__ ((unused)))
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
		_puts("\n");
	}
}

/**
 * setEnvironmentVariable - Initialize a new environment
 * variable, or modify an existing one
 * @argv: array of entered words
 */

void setEnvironmentVariable(char **argv)
{
	int i, j, k;

	if (!argv[1] || !argv[2])
	{
		perror(getEnvironmentVariable("_"));
		return;
	}

	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (argv[1][j] == environ[i][j])
		{
			while (argv[1][j])
			{
				if (argv[1][j] != environ[i][j])
					break;

				j++;
			}
			if (argv[1][j] == '\0')
			{
				k = 0;
				while (argv[2][k])
				{
					environ[i][j + 1 + k] = argv[2][k];
					k++;
				}
				environ[i][j + 1 + k] = '\0';
				return;
			}
		}
	}
	if (!environ[i])
	{
		environ[i] = concatenateStrings(argv[1], "=", argv[2]);
		environ[i + 1] = '\0';
	}
}

/**
 * unsetEnvironmentVariable - Remove an environment variable
 * @argv: array of entered words
 */

void unsetEnvironmentVariable(char **argv)
{
	int i, j;

	if (!argv[1])
	{
		perror(getEnvironmentVariable("_"));
		return;
	}
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (argv[1][j] == environ[i][j])
		{
			while (argv[1][j])
			{
				if (argv[1][j] != environ[i][j])
					break;

				j++;
			}
			if (argv[1][j] == '\0')
			{
				free(environ[i]);
				environ[i] = environ[i + 1];
				while (environ[i])
				{
					environ[i] = environ[i + 1];
					i++;
				}
				return;
			}
		}
	}
}

/**
 * splitString - splits a string and makes it an array of pointers to words
 * @str: the string to be split
 * @delim: the delimiter
 * Return: array of pointers to words
 */
char **splitString(char *str, const char *delim)
{
	int i, wn;
	char **array;
	char *token;
	char *copy;

	copy = malloc(stringLength(str) + 1);
	if (copy == NULL)
	{
		perror(getEnvironmentVariable("_"));
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';

	token = strtok(copy, delim);
	array = malloc((sizeof(char *) * 2));
	array[0] = stringDuplicate(token);

	i = 1;
	wn = 3;
	while (token)
	{
		token = strtok(NULL, delim);
		array = reallocateArray(array, (sizeof(char *) * (wn - 1))
				, (sizeof(char *) * wn));
		array[i] = stringDuplicate(token);
		i++;
		wn++;
	}
	free(copy);
	return (array);
}

/**
 * executeCommand - executes a command
 * @argv: array of arguments
 */
void executeCommand(char **argv)
{
	int d, status;

	if (!argv || !argv[0])
		return;

	d = fork();
	if (d == -1)
	{
		perror(getEnvironmentVariable("_"));
	}
	if (d == 0)
	{
		execve(argv[0], argv, environ);
		perror(argv[0]);
		exit(EXIT_FAILURE);
	}
	wait(&status);
}
