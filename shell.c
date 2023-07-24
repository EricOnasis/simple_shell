#include "shell.h"

/**
 * main - Shell
 * Return: 0 on success
 */

int main(void)
{
	char *buff = NULL, *value, *pathname, **args;
	void (*func)(char **);
	ssize_t len = 0;
	list_path *head = NULL;
	size_t size = 0;

	signal(SIGINT, sig_handler);
	while (len != EOF)
	{
		check_isatty();
		len = getline(&buff, &size, stdin);
		handle_eof(len, buff);
		args = split_string(buff, " \n");
		if (!args || !args[0])
			execute_command(args);
		else
		{
			value = _getenv("PATH");
			head = create_path_list(value);
			pathname = find_executable_path(args[0], head);
			func = get_builtin_function(args);
			if (func)
			{
				free(buff);
				func(args);
			}
			else if (!pathname)
				execute_command(args);
			else if (pathname)
			{
				free(args[0]);
				args[0] = pathname;
				execute_command(args);
			}
		}
	}
	free_path_list(head);
	free_arguments(args);
	free(buff);
	return (0);
}
