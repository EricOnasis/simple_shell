#include "shell.h"

/**
 * reallocateArray - Reallocates memory block for array of strings
 * @ptr: previous pointer
 * @oldSize: old size of previous pointer
 * @newSize: new size for our pointer
 * Return: New resized pointer
 */

void *reallocateArray(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	char *new;
	char *old;

	unsigned int i;

	if (ptr == NULL)
		return (malloc(newSize));

	if (newSize == oldSize)
		return (ptr);

	if (newSize == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new = malloc(newSize);
	old = ptr;
	if (new == NULL)
		return (NULL);

	if (newSize > oldSize)
	{
		for (i = 0; i < oldSize; i++)
			new[i] = old[i];
		free(ptr);
		for (i = oldSize; i < newSize; i++)
			new[i] = '\0';
	}
	if (newSize < oldSize)
	{
		for (i = 0; i < newSize; i++)
			new[i] = old[i];
		free(ptr);
	}
	return (new);
}

/**
 * freeArray - frees the array of pointers arv
 * @array: array of pointers
 */
void freeArray(char **array)
{
	int i;

	for (i = 0; array[i]; i++)
		free(array[i]);
	free(array);
}

/**
 * checkBuiltin - checks if the command is a builtin
 * @argv: array of arguments
 * Return: pointer to function that takes argv and returns void
 */

void (*checkBuiltin(char **argv))(char **argv)
{
	int i, j;
	BuiltinCommand commands[] = {
		{"exit", exitShell},
		{"env", printEnvironment},
		{"setenv", setEnvironmentVariable},
		{"unsetenv", unsetEnvironmentVariable},
		{NULL, NULL}
	};

	for (i = 0; commands[i].name; i++)
	{
		j = 0;
		if (commands[i].name[j] == argv[0][j])
		{
			for (j = 0; argv[0][j]; j++)
			{
				if (commands[i].name[j] != argv[0][j])
					break;
			}
			if (!argv[0][j])
				return (commands[i].func);
		}
	}
	return (NULL);
}

/**
 * getEnvironmentVariable - gets the value of the environment variable
 * @name: name of the environment variable
 * Return: string of value
 */

char *getEnvironmentVariable(const char *name)
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

/**
 * addNodeEnd - adds a new node at the end of a linked list
 * @head: pointer to pointer to the head of the linked list
 * @str: pointer to string in the previous first node
 * Return: address of the new element/node
 */

LinkedListNode *addNodeEnd(LinkedListNode **head, char *str)
{
	LinkedListNode *tmp;
	LinkedListNode *newNode;

	newNode = malloc(sizeof(LinkedListNode));

	if (!newNode || !str)
	{
		return (NULL);
	}

	newNode->dir = str;
	newNode->next = (NULL);

	if (!*head)
	{
		*head = newNode;
	}
	else
	{
		tmp = *head;

		while (tmp->next)
		{
			tmp = tmp->next;
		}

		tmp->next = newNode;
	}

	return (*head);
}

