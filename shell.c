#include "shell.h"

/**
 * main - main arguments functions
 * @argc: count of arguments
 * @argv: arguments
 * @env: environment
 * Return: _exit = 0.
 */

/**
 * main - Main arguments function
 * @argc: Count of arguments
 * @argv: Arguments
 * @envp: Environment
 * Return: _exit = 0
 */


int main(int argc, char **argv, char **envp)
{
	char *userInput = NULL, **userTokens = NULL;
	int pathValue = 0, exitCode = 0, n = 0;
	(void)argc;

	while (1)
	{
		userInput = get_user_input();
		if (userInput)
		{
			pathValue++;
			userTokens = tokenize_input(userInput);
			if (!userTokens)
			{
				free(userInput);
				continue;
			}

			if ((!_strcmp(userTokens[0], "exit")) && userTokens[1] == NULL)
				exit_command(userTokens, userInput, exitCode);
			if (!_strcmp(userTokens[0], "env"))
				print_env(envp);
			else
			{
				n = find_path(userTokens, envp);
				exitCode = fork_and_execute(userTokens, argv, envp, userInput, pathValue, n);
				if (n == 0)
					free(userTokens[0]);
			}

			free(userTokens);
		}
		else
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			exit(exitCode);
		}

		free(userInput);
	}

	return (exitCode);
}