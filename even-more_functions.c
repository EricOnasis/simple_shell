#include "shell.h"

/**
 * add_path_node_end - Adds a new node at the end of a list_path list
 * @head: Pointer to pointer to our linked list
 * @dir: Pointer to directory in previous first node
 * Return: Address of the new element/node
 */
list_path *add_path_node_end(list_path **head, char *dir)
{
	list_path *tmp, *new_node;

	new_node = malloc(sizeof(list_path));
	if (new_node == NULL)
		return (NULL);

	new_node->dir = _strdup(dir);
	new_node->p = NULL;

	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		tmp = *head;
		while (tmp->p)
			tmp = tmp->p;

		tmp->p = new_node;
	}

	return (*head);
}

/**
 * create_path_list - creates a linked list for path directories
 * @path: string of path value
 * Return: pointer to the created linked list
 */
list_path *create_path_list(char *path)
{
	list_path *head = NULL;
	char *token;
	char *copy_path = _strdup(path);

	token = strtok(copy_path, ":");
	while (token != NULL)
	{
		head = add_path_node_end(&head, token);
		token = strtok(NULL, ":");
	}

	free(copy_path);
	return (head);
}

/**
 * find_executable_path - finds the pathname of an executable file
 * @filename: Name of file or command
 * @head: Head of linked list of path directories
 * Return: Pathname of filename or NULL if no match
 */
char *find_executable_path(char *filename, list_path *head)
{
	struct stat st;
	char *pathname;
	list_path *tmp = head;

	while (tmp != NULL)
	{
		pathname = concat_all(tmp->dir, "/", filename);
		if (stat(pathname, &st) == 0)
			return (pathname);
		free(pathname);
		tmp = tmp->p;
	}

	return (NULL);
}

/**
 * free_path_list - frees a list_path
 * @head: pointer to our linked list
 */
void free_path_list(list_path *head)
{
	list_path *current = head;
	list_path *next;

	while (current != NULL)
	{
		next = current->p;
		free(current->dir);
		free(current);
		current = next;
	}
}

/**
 * sig_handler - checks if Ctrl C is pressed
 * @sig_num: int
 */
void sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
		_puts("\n$ ");
}
