#include "shell.h"

/**
 * tokenize_input - get token of string
 * @line: command user
 * Return: To a pointer
 */

char **tokenize_input(char *line)
{
	char **user_command = NULL;
	char *token = NULL;
	size_t i = 0;
	int size = 0;

	if (line == NULL)
		return (NULL);

	for (i = 0; line[i]; i++)
	{
		if (line[i] == ' ')
			size++;
	}

	if ((size + 1) == _strlen(line))
		return (NULL);

	user_command = malloc(sizeof(char *) * (size + 2));
	if (user_command == NULL)
		return (NULL);

	token = _strtok(line, " \n\t\r");
	for (i = 0; token != NULL; i++)
	{
		user_command[i] = token;
		token = _strtok(NULL, " \n\t\r");
	}
	user_command[i] = NULL;
	return (user_command);
}

/**
 * _strtok - breaks the string s1 into tokens and null-terminates them.
 * Delimiter-Characters at the beginning and end
 *of str are skipped. On each subsequent call delim may change.
 * @str: string to tokenize
 * @delim: string with the character that delimit srt.
 * Return: the first/next token if possible, a null-pointer otherwise.
 **/

char *_strtok(char *str, const char *delim)
{
	static char *p;

	if (str)
		p = str;
	else if (!p)
		return (NULL);

	str = p + _strspn(p, delim);
	p = str + _strcspn(str, delim);
	if (p == str)
		return (p = (NULL));
	p = *p ? *p = 0, p + 1 : NULL;
	return (str);
}
