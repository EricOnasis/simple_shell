#include "shell.h"

/**
 * createPathList - creates a linked list for path directories
 * @path: string of path value
 * Return: pointer to the created linked list
 */
PathList *createPathList(char *path)
{
	PathList *head = NULL;
	char *token;
	char *copyPath = stringDuplicate(path);

	token = strtok(copyPath, ":");
	while (token)
	{
		head = addNodeEnd(&head, token);
		token = strtok(NULL, ":");
	}

	return (head);
}

/**
 * findPathname - finds the pathname of a filename
 * @filename: name of file or command
 * @head: head of linked list of path directories
 * Return: pathname of filename or NULL if no match
 */
char *findPathname(char *filename, PathList *head)
{
	struct stat st;
	char *pathname;

	PathList *tmp = head;

	while (tmp)
	{
		pathname = concatenateStrings(tmp->dir, "/", filename);
		if (stat(pathname, &st) == 0)
		{
			return (pathname);
		}
		free(pathname);
		tmp = tmp->next;
	}

	return (NULL);
}

/**
 * freePathList - frees a PathList
 * @head: pointer to our linked list
 */
void freePathList(PathList *head)
{
	PathList *storage;

	while (head)
	{
		storage = head->next;
		free(head->dir);
		free(head);
		head = storage;
	}
}

