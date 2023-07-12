/**
 * main - Main shell function
 * Return: 0 on success
 */
int main(void)
{
	ssize_t input_length = 0;
	char *input_buffer = NULL, *path_value, *full_pathname, **command_arguments;
	size_t buffer_size = 0;
	list_path *directory_list = '\0';
	void (*command_function)(char **);

	signal(SIGINT, handle_sigint);
	while (input_length != EOF)
	{
		print_prompt_if_tty();
		input_length = getline(&input_buffer, &buffer_size, stdin);
		handle_eof(input_length, input_buffer);
		command_arguments = splitstring(input_buffer, " \n");
		if (!command_arguments || !command_arguments[0])
			execute(command_arguments)
		else
		{
			path_value = _getenv("PATH");
			directory_list = linkpath(path_value);
			full_pathname = _which(command_arguments[0], directory_list);
			command_function = checkbuild(command_arguments);
			if (command_function)
			{
				free(input_buffer);
				command_function(command_arguments);
			}
			else if (!full_pathname)
				execute(command_arguments);
			else if (full_pathname)
			{
				free(command_arguments[0]);
				command_arguments[0] = full_pathname;
				execute(command_arguments);
			}
		}
	}
	free_list(directory_list);
	freearv(command_arguments);
	free(input_buffer);
	return (0);
}
