#include "header.h"
/**
 * _strdup - function that duplicates a string
 * @src: source string to be duplicated
 * Return: pointer to duplicated string or NULL
 */
char *_strdup(const char *src)
{
	char *dest;

	if (src == NULL)
	{
		return (NULL);
	}
	dest = (char *) malloc(_strlen(src) + 1);
	if (dest == NULL)
	{
		return (NULL);
	}
	_strcpy(dest, src);
	return (dest);
}

/**
 * _strcmp - function that compares two strings
 * @s1: first string
 * @s2: second string
 * Return: int (0 if strings are equal, non-zero if strings are not equal)
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * _isspace - a function which checks if whitespace
 * @x: the character
 * Return: if whitespace (1), if not (0)
 */
bool _isspace(int x)
{
	return (x == ' ' || (x >= 0x09 && x <= 0x0d));
}
