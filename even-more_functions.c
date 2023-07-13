#include "shell.h"

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
 * find_executable_path - finds the pathname of an executable file
 * @filename: name of file or command
 * @head: head of linked list of path directories
 * Return: pathname of filename or NULL if no match
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
 * add_path_node_end - adds a new node at the end of a list_path list
 * @head: pointer to pointer to our linked list
 * @dir: pointer to directory in previous first node
 * Return: address of the new element/node
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
