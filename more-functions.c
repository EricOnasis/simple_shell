#include "shell.h"

/**
 * check_isatty - checks if the shell is running in a terminal
 */
void check_isatty(void)
{
	if (isatty(STDIN_FILENO))
		_puts("#cisfun$ ");
}


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
 * sig_handler - checks if Ctrl C is pressed
 * @sig_num: int
 */
void sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
		_puts("\n#cisfun$ ");
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

