#include "shell.h"

/**
 * handle_eof - handles the End of File
 * @len: return value of getline function
 * @buff: buffer
 */

void handle_eof(int len, char *buff)
{
	if (len == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			_puts("\n");
			free(buff);
		}
		exit(0);
	}
}

/**
 * check_isatty - checks whether the shell is running in a terminal
 */

void check_isatty(void)
{
	if (isatty(STDIN_FILENO))
		_puts("$ ");
}


/**
 * _puts - prints a string
 * @str: pointer to string
 */

void _puts(char *str)
{
	int i = 0;

	while (str[i])
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * split_string - splits a string and makes it an array
 * @str: the string to be split
 * @delim: the delimiter
 * Return: the array
 */

char **split_string(char *str, const char *delim)
{
	int i, wn;
	char **array;
	char *token;
	char *copy;

	copy = _strdup(str);
	if (copy == NULL)
	{
		perror("Memory allocation failed");
		return (NULL);
	}

	i = 0;
	while (copy[i])
	{
		i++;
	}
	copy[i] = '\0';

	token = strtok(copy, delim);
	array = malloc(sizeof(char *) * 2);
	array[0] = _strdup(token);

	i = 1;
	wn = 3;
	while (token)
	{
		token = strtok(NULL, delim);
		array = realloc(array, sizeof(char *) * wn);
		array[i] = _strdup(token);
		i++;
		wn++;
	}
	free(copy);
	return (array);
}
