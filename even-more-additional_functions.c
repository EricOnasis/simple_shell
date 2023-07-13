#include "shell.h"

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
