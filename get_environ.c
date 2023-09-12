#include "header.h"
/**
 * _getenviron - search inside environ
 * @name: the name to search
 * Return: the environ or NUll
*/
char *_getenviron(char *name)
{
	char **env = environ;

	int i = 0;

	char *token = NULL;

	while (env[i])
	{
		token = strtok(env[i], "=");
		if (strcmp(name, token) == 0)
			return (strtok(NULL, "="));
		i++;
	}
	return (NULL);
}
/**
 * get_command - search inside path the file
 * @command: the command
 * Return: command or NULL if failed
*/
char *get_command(char *command)
{
	char *path = _getenviron("PATH");

	char *full_com;

	char *token;

	token = strtok(path, ":");

	while (token)
	{
		full_com = malloc(sizeof(char) * (strlen(token) + strlen(command) + 2));
		strcpy(full_com, token);
		strcat(full_com, "/");
		strcat(full_com, command);
		if (access(full_com, F_OK) == 0)
			return (full_com);
		free(full_com);
		token = strtok(NULL, ":");
	}
	return (NULL);
}
