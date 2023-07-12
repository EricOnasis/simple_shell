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
	}
	free_list(directory_list);
	freearv(command_arguments);
	free(input_buffer);
	return (0);
}
