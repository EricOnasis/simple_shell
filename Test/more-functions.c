#include "shell.h"

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
 * free_arguments - frees the array of pointers args
 * @args: array of pointers
 */
void free_arguments(char **args)
{
	int i;

	for (i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}

/**
 * _getenv - gets the value of the global variable
 * @name: name of the global variable
 * Return: string of value
 */
char *_getenv(const char *name)
{
	int i, j;
	char *value;

	if (!name)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (name[j] == environ[i][j])
		{
			while (name[j])
			{
				if (name[j] != environ[i][j])
					break;

				j++;
			}
			if (name[j] == '\0')
			{
				value = (environ[i] + j + 1);
				return (value);
			}
		}
	}

	return (NULL);
}
