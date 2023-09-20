#include "header.h"
/**
* print_env - function that print environ
* Return: 0
*/
int print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
/**
 * _getenviron - function that get the environ
 * @name: name to search
 * Return: char (the environ) or NULL if it fail
*/
char *_getenviron(const char *name)
{
	char *token;
	char *env_variable;
	char *value;
	int i = 0;

	while (environ[i])
	{
		env_variable = strdup(environ[i]);
		if (env_variable == NULL)
			return (NULL);
		token = strtok(env_variable, "=");
		if (token != NULL && (strcmp(name, token) == 0))
		{
			token = strtok(NULL, "=");
			value = strdup(token);
			free(env_variable);
			return (value);
		}
		free(env_variable);
		i++;
	}
	return (NULL);
}
/**
 * split_array - function that split command
 * into token with delimiter (space)
 * @buffer: the buffer
 * @len_buffer: len of the buffer
 * Return: array
*/
char **split_array(char *buffer, int len_buffer)
{
	char **array;
	char *token;
	int i = 0;

	array = malloc(sizeof(char *) * (len_buffer + 1));
	if (array == NULL)
		return (NULL);
	token = strtok(buffer, " \t\n");
	while (token)
	{
		array[i] = malloc(sizeof(char) * (strlen(token) + 1));
		strcpy(array[i], token);
		token = strtok(NULL, " \t\n");
		i++;
	}
	array[i] = NULL;
	return (array);
}
/**
 * check_path - function that check the cmd
 * if it exit in the path
 * @cmd: cmd enter by the user
 * Return: the cmd or null
*/
char *check_path(char *cmd)
{
	char *path = _getenviron("PATH");
	char *token;
	char *full_cmd;

	if (path == NULL || cmd == NULL)
		return (NULL);
	token = strtok(path, ":");
	while (token)
	{
		full_cmd = malloc(sizeof(char) * (strlen(token) + strlen(cmd) + 2));
		if (full_cmd == NULL)
		{
			free(path);
			return (NULL);
		}
		strcpy(full_cmd, token);
		strcat(full_cmd, "/");
		strcat(full_cmd, cmd);
		if (access(full_cmd, F_OK) == 0)
		{
			free(path);
			return (full_cmd);
		}
		free(full_cmd);
		token = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}
/**
 * handle_exit - function that free before exit
 * @arrays: the array
*/
void handle_exit(char **arrays)
{
	int i = 0;

	while (arrays[i])
	{
		free(arrays[i]);
		i++;
	}
	free(arrays[i]);
	free(arrays);
	exit(0);
}

