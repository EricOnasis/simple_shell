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


