#include "shell.h"

/**
 * handle_sigint - checks if Ctrl+C is pressed
 * @signal_number: the pressed character
 */

void handle_sigint(int signal_number)
{
	if (signal_number == SIGINT)
	{
		_puts("\n$ ");
	}
}

/**
 * handle_eof - handles the End of File condition
 * @line_length: return value of getline function
 * @buffer: buffer
 */

void handle_eof(int line_length, char *buffer)
{
	(void)buffer;
	if (line_length == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			_puts("\n");
			free(buffer);
		}
		exit(0);
	}
}

/**
 * print_prompt_if_tty - prints the shell prompt if input is from a terminal
 */

void print_prompt_if_tty(void)
{
	if (isatty(STDIN_FILENO))
		_puts("$ ");
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
