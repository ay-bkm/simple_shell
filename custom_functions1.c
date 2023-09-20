#include "header.h"

/**
 * _strlen - function that calculates the length of a string
 * @s: string to calculate length of
 * Return: int (length of string)
 */
int _strlen(const char *s)
{
	int len = 0; /* Initialize length to 0 */

	while (s[len] != '\0')
	{ /* Loop through each character in string */
		len++; /* Increment length */
	}

	return (len); /* Return length */
}

/**
 * _strchr - function that finds the first occurrence of character in a string
 * @s: string to search in
 * @c: character to search for
 * Return: char* (pointer to 1st occurrence of character or NULL if not found)
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{ /* Loop through each character in string */
		if (*s == c)
		{ /* If character matches */
			return (s); /* Return pointer to character */
		}
		s++; /* Move to next character */
	}

	return (NULL); /* Return NULL if character is not found */
}

/**
 * _strcat - function that concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: char* (pointer to destination string)
 */
char *_strcat(char *dest, char *src)
{
	int i = 0; /* Initialize index to 0 */
	int j = 0; /* Initialize index to 0 */

	while (dest[i] != '\0')
	{ /* Find end of destination string */
		i++;
	}

	while (src[j] != '\0')
	{ /* Loop through each character in source string */
		dest[i] = src[j]; /* Append character to destination string */
		i++;
		j++;
	}

	dest[i] = '\0'; /* Null terminate destination string */

	return (dest); /* Return destination string */
}

/**
 * _strcpy - function that copies a string
 * @dest: destination string
 * @src: source string
 * Return: char* (pointer to destination string)
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0; /* Initialize index to 0 */

	while (src[i] != '\0')
	{ /* Loop through each character in source string */
		dest[i] = src[i]; /* Copy character to destination string */
		i++;
	}

	dest[i] = '\0'; /* Null terminate destination string */

	return (dest); /* Return destination string */
}
