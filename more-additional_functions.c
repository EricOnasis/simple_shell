#include "shell.h"

/**
 * _realloc - Reallocates memory block
 * @ptr: previous pointer
 * @old_size: old size of previous pointer
 * @new_size: new size for our pointer
 * Return: New resized Pointer
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			new_ptr[i] = *((char *)ptr + i);

		for (; i < new_size; i++)
			new_ptr[i] = '\0';
	}
	else
	{
		for (i = 0; i < new_size; i++)
			new_ptr[i] = *((char *)ptr + i);
	}

	free(ptr);
	return (new_ptr);
}

/**
 * execute_command - executes a command
 * @args: array of arguments
 */

void execute_command(char **args)
{
	pid_t pid;
	int status;

	if (!args || !args[0])
		return;

	pid = fork();
	if (pid == -1)
	{
		perror(_getenv("_"));
	}
	if (pid == 0)
	{
		execve(args[0], args, environ);
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * get_builtin_function - checks if the command is a built-in function
 * @args: array of arguments
 * Return: pointer to function that takes args and returns void
 */
void (*get_builtin_function(char **args))(char **args)
{
	int i, j;
	builtin_func_table table[] = {
		{"exit", exit_shell},
		{"env", print_environment},
		{"setenv", set_environment_variable},
		{"unsetenv", unset_environment_variable},
		{NULL, NULL}};
	for (i = 0; table[i].name; i++)
	{
		j = 0;
		if (table[i].name[j] == args[0][j])
		{
			while (args[0][j])
			{
				if (table[i].name[j] != args[0][j])
					break;
				j++;
			}
			if (!args[0][j])
				return (table[i].func);
		}
	}
	return (NULL);
}

/**
 * print_environment - prints the current environment
 * @args: array of arguments
 */
void print_environment(char **args)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
		_puts("\n");
	}

	free_arguments(args);
}
