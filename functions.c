#include "shell.h"

/**
 * concatenate - concats 3 strings in a newly allocated memory
 * @name: first string
 * @sep: second string
 * @value: Third string
 * Return: pointer to the new string
 */

char *concatenate(char *name, char *sep, char *value)
{
	int len1, len2, len3, total_len, i, j;
	char *result;

	len1 = strlen(name);
	len2 = strlen(sep);
	len3 = strlen(value);
	total_len = len1 + len2 + len3;

	result = malloc(sizeof(char) * (total_len + 1));
	if (result == NULL)
		return (NULL);

	for (i = 0; i < len1; i++)
		result[i] = name[i];
	for (j = 0; j < len2; j++)
		result[i + j] = sep[j];
	for (j = 0; j < len3; j++)
		result[i + j + len2] = value[j];
	result[i + j + len2] = '\0';

	return (result);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory, which
 * contains a copy of the string given as a parameter
 * @str: pointer to a string
 * Return: pointer to a string
 */

char *_strdup(char *str)
{
	if (str == NULL)
		return (NULL);

	int len = strlen(str);
	char *dup = malloc(sizeof(char) * (len + 1));

	if (dup == NULL)
		return (NULL);

	strcpy(dup, str);
	return (dup);
}

/**
 * split_string - splits a string and makes it an array of pointers to words
 * @str: the string to be split
 * @delim: the delimiter
 * Return: array of pointers to words
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

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
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
