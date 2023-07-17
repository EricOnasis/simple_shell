#include "shell.h"

/**
 * _strdup - returns a pointer to a newly allocated space in memory, which
 * contains a copy of the string given as a parameter
 * @str: pointer to a string
 * Return: pointer to a string
 */

char *_strdup(char *str)
{
	int len = strlen(str);
	char *dup = malloc(sizeof(char) * (len + 1));

	if (str == NULL)
		return (NULL);

	strcpy(dup, str);
	return (dup);
}

/**
 * concat_all - concats 3 strings in a newly allocated memory
 * @name: first string
 * @sep: second string
 * @value: Third string
 * Return: pointer to the new string
 */

char *concat_all(char *name, char *sep, char *value)
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
