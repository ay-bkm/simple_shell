#include "header.h"
/**
 * free_args - function that free agrs
 * @args: array of string
*/
void free_args(char **args)
{
	int i = 0;

	while (args[i])
	{
		free(args[i]);
		i++;
	}
	if (args[i] == NULL)
		free(args[i]);
	free(args);
}
