#include "header.h"
/**
 * execute_command - function that execute command
 * @args: the array contain the command
 * Return: 0 or 127 if it fail
*/
int execute_command(char **args)
{
	pid_t pid;
	char *command;
	int status = 0;
	int exit_status = 0;

	pid = fork();
	if (pid == 0)
	{
		if (access(args[0], F_OK) == 0)
			execve(args[0], args, environ);
		else
		{
			command = check_path(args[0]);
			if (command)
			{
				execve(command, args, environ);
				free(command);
			}
			else
			{
				write(STDERR_FILENO, "./hsh: 1: ", 11);
				write(STDERR_FILENO, args[0], strlen(args[0]));
				write(STDERR_FILENO, ": not found\n", 13);
				exit(127);
			}
		}
	}
	else if (pid < 0)
		perror("fork");
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			return (exit_status);
		}
	}
	return (0);
}
/**
 * shell_interactive - function loop
 *
 * Return: status
*/
int shell_interactive(void)
{
	char **args;
	char *buffer = NULL;
	size_t buf_size = 0;
	ssize_t n_read;
	int i, contain_all_space, status = 0;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 10);
		n_read = getline(&buffer, &buf_size, stdin);
		if (n_read == EOF)
		{
			free(buffer);
			break;
		}
		if (n_read > 0 && buffer[n_read - 1] == '\n')
			buffer[n_read - 1] = '\0'; /* Remove newline character if it exists */
		contain_all_space = 1;
		for (i = 0; i < n_read - 1; i++)
		{
			if (buffer[i] != ' ')
				contain_all_space = 0;
		}
		if (contain_all_space) /* Handle the case where the input is only spaces*/
			continue; /* Skip processing and prompt for the next input*/
		args = split_array(buffer, strlen(buffer));
		if (strcmp(args[0], "env") == 0)
			status = print_env();
		else if (strcmp(args[0], "exit") == 0)
			free(buffer), handle_exit(args);
		else
			status = execute_command(args), free_args(args);
		free(buffer), buffer = NULL;
	}
	return (status); /* Return status at the end of the loop */
}

/**
 * shell_non_interaction - function that handle
 * non interactive mode
 * Return: status
*/
int shell_non_interaction(void)
{
	char *line = NULL;
	int status, i, n_read;
	int contain_all_space;
	size_t size = 0;
	char **args = NULL;

	while ((n_read = getline(&line, &size, stdin)) > 0)
	{

		contain_all_space = 1;
		for (i = 0; i < n_read - 1; i++)
		{
			if (line[i] != ' ')
				contain_all_space = 0;
		}
		if (contain_all_space) /* Handle the case where the input is only spaces*/
			continue; /* Skip processing and prompt for the next input*/
		args = split_array(line, strlen(line));
		if (strcmp(args[0], "exit") == 0)
			handle_exit(args);
		if (strcmp(args[0], "env") == 0)
			status = print_env();
		else
			status = execute_command(args), free_args(args);
		free(line);
		line = NULL;
	}
	return (status);
}

