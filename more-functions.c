#include "shell.h"

/**
 * duplicate_string - Returns a pointer to a newly allocated space in memory,
 * containing a copy of the string given as a parameter.
 * @source: Pointer to the source string.
 * Return: Pointer to the duplicated string.
 */
char *duplicate_string(char *source)
{
	int i, source_length;
	char *new_string;

	if (!source)
	{
		return (NULL);
	}

	source_length = 0;
	while (source[source_length] != '\0')
	{
		source_length++;
	}

	new_string = malloc(sizeof(char) * (source_length + 1));
	if (!new_string)
	{
		return (NULL);
	}

	for (i = 0; i < source_length; i++)
	{
		new_string[i] = source[i];
	}
	new_string[source_length] = '\0';

	return (new_string);
}

/**
 * concatenate_strings - Concatenates three strings
 * into a newly allocated memory.
 * @str1: First string.
 * @str2: Second string.
 * @str3: Third string.
 * Return: Pointer to the concatenated string.
 */
char *concatenate_strings(char *str1, char *str2, char *str3)
{
	char *result;
	int len1, len2, len3, i, j;

	len1 = calculate_string_length(str1);
	len2 = calculate_string_length(str2);
	len3 = calculate_string_length(str3);

	result = malloc(sizeof(char) * (len1 + len2 + len3 + 1));
	if (!result)
		return (NULL);

	for (i = 0; i < len1; i++)
		result[i] = str1[i];
	j = i;

	for (i = 0; i < len2; i++)
		result[j + i] = str2[i];
	j += i;

	for (i = 0; i < len3; i++)
		result[j + i] = str3[i];
	j += i;

	result[j] = '\0';

	return (result);
}

/**
 * calculate_string_length - Calculates the length of a string.
 * @str: Pointer to the string.
 * Return: The length of the string.
 */
int calculate_string_length(char *str)
{
	int length = 0;

	while (*(str + length) != '\0')
	{
		length++;
	}
	return (length);
}

/**
 * exitShell - exits the shell with or without a return of status n
 * @argv: array of words of the entered line
 */
void exitShell(char **argv)
{
	int i, n;

	if (argv[1])
	{
		n = convertToInt(argv[1]);
		if (n <= -1)
			n = 2;
		freeArgs(argv);
		exit(n);
	}

	for (i = 0; argv[i]; i++)
		free(argv[i]);

	free(argv);
	exit(0);
}

/**
 * convertToInt - converts a string into an integer
 * @s: pointer to a string
 * Return: the integer
 */
int convertToInt(char *s)
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
