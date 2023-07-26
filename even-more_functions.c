#include "shell.h"
/**
 * _strcspn - computes the length of the maximum initial segment of the string
 * pointed to by s1which consists entirely of characters not from the
 * string pointed to by s2.
 * @s1: string to check
 * @s2: string useful to compare
 * Return: the length of the segment.
 **/
size_t _strcspn(const char *s1, const char *s2)
{
	size_t ret = 0;

	while (*s1)
	{
		if (_strchr(s2, *s1))
			return (ret);
		s1++, ret++;
	}
	return (ret);
}
/**
 * _strspn - computes the length of the maximum initial segment of the string
 * pointed to by s1 which consists entirely of characters from the string
 * pointed to by s2.
 * @s1: strint to compute the lengh
 * @s2: string delimit
 * Return: the length of the segment.
 **/
size_t _strspn(const char *s1, const char *s2)
{
	size_t ret = 0;

	while (*s1 && _strchr(s2, *s1++))
		ret++;
	return (ret);
}
/**
 * _strchr - locates the ﬁrst occurrence of c (converted to a char) in the
 * string pointed to by s. The terminating null character is considered to be
 * part of the string.
 * @s: string
 * @c: character
 * Return: a pointer to the located character, or a null pointer
 * if the character does not occur in the string.
 **/
char *_strchr(const char *s, int c)
{
	while (*s != (char)c)
		if (!*s++)
			return (0);
	return ((char *)s);
}

/**
 *_strcat - copy string to another string.
 *@dest: char
 *@src: char
 *Return: dest
 *
 */

char *_strcat(char *dest, char *src)
{
	int d = 0;
	int s = 0;

	while (dest[d] != '\0')
	{
		d++;
	}
	while (src[s] != '\0')
	{
		dest[d] = src[s];
		d++;
		s++;
	}
	dest[d] = '\0';
	return (dest);
}


/**
 * _strcmp - compare the values of a string
 * @s1: character
 * @s2: character
 * Return: 0
 */

int _strcmp(char *s1, char *s2)
{
	int a;

	for (a = 0; s1[a] != '\0' && s2[a] != '\0'; a++)
	{
		if (s1[a] != s2[a])
			return ((int)s1[a] - s2[a]);
	}
	return (0);
}
