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
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
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
		env_variable = _strdup(environ[i]);
		if (env_variable == NULL)
			return (NULL);
		token = strtok(env_variable, "=");
		if (token != NULL && (_strcmp(name, token) == 0))
		{
			token = strtok(NULL, "=");
			value = _strdup(token);
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
	int i = 0, j = 0;

	array = malloc(sizeof(char *) * (len_buffer + 1));
	if (array == NULL)
		return (NULL);

	array[i] = &buffer[j];
	while (buffer[j] != '\0')
	{
		if (buffer[j] == ' ' || buffer[j] == '\t' || buffer[j] == '\n')
		{
			buffer[j] = '\0';
			i++;
			array[i] = &buffer[j + 1];
		}
		j++;
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
		full_cmd = malloc(sizeof(char) * (_strlen(token) + _strlen(cmd) + 2));
		if (full_cmd == NULL)
		{
			free(path);
			return (NULL);
		}
		_strcpy(full_cmd, token);
		_strcat(full_cmd, "/");
		_strcat(full_cmd, cmd);
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

