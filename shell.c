#include "shell.h"

/**
 * main - Shell
 * Return: 0 on success
 */

int main(void)
{
	list_path *pathHead = NULL;
	void (*builtinFunc)(char **);
	ssize_t length = 0;
	char *buffer = NULL, **arguments = NULL, *envValue = NULL, *execPath = NULL;
	size_t bufferSize = 0;

	signal(SIGINT, sig_handler);
	while (length != EOF)
	{
		check_isatty();
		length = getline(&buffer, &bufferSize, stdin);
		handle_eof(length, buffer);
		arguments = split_string(buffer, " \n");
		if (arguments && arguments[0])
		{
			envValue = _getenv("PATH");
			pathHead = create_path_list(envValue);
			execPath = find_executable_path(arguments[0], pathHead);
			builtinFunc = get_builtin_function(arguments);
			if (builtinFunc)
			{
				builtinFunc(arguments);
			}
			else if (!execPath)
			{
				execute_command(arguments);
			}
			else
			{
				free(arguments[0]), arguments[0] = execPath,
					execute_command(arguments);
			}
			free_path_list(pathHead);
		}
		free(buffer);		
	}

	return (0);
}
