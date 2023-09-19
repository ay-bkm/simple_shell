#include "header.h"

/**
 * execute_command - Executes a command specified by the args array.
 * @args: The array containing the command and its arguments.
 * Return: The exit status of the executed command.
 */
int execute_command(char **args)
{
	pid_t pid;
	char *command;
	int status;
	int exit_status;

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
			}
			else
			{
				fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
				exit(127);
			}
		}
	}
	else if (pid < 0)
	{
		perror("fork");
	}
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
 * shell_interactive - Handles the interactive mode of the shell.
 * Return: The exit status of the shell.
 */
int shell_interactive(void)
{
	char **args, *buf = NULL;
	size_t size = 0;
	int n, status, i, is_empty;

	while (printf("#cisfun$ "), n = getline(&buf, &size, stdin), n != -1)
	{
		if (n > 1 && buf[n - 1] == '\n')
			buf[--n] = 0;
		is_empty = 1;

		for (i = 0; i < n; i++)
			if (buf[i] != ' ')
				is_empty = 0;
		if (is_empty)
			continue;
		args = split_array(buf, n);
		if (strcmp(args[0], "env") == 0)
			status = print_env();
		else if (strcmp(args[0], "exit") == 0)
			free(buf), handle_exit(args);
		else
		{
			status = execute_command(args);
			if (status == 127)
				fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		}
		free_args(args);
	}
	if (n == -1 && feof(stdin))
		printf("\n"), free(buf), exit(status);
	perror("getline failed");
	exit(1);
}



/**
 * shell_non_interaction - Handles the non-interactive mode of the shell.
 * Return: The exit status of the shell.
 */
int shell_non_interaction(void)
{
	char *line = NULL;
	int status;
	size_t size = 0;
	char **args = NULL;

	while (getline(&line, &size, stdin) > 0)
	{
		/* Split the input into arguments */
		args = split_array(line, strlen(line));

		/* Check for built-in commands or execute external commands */
		if (strcmp(args[0], "exit") == 0)
			handle_exit(args);
		if (strcmp(args[0], "env") == 0)
			status = print_env();
		else
		{
			/* Execute the command and handle errors */
			status = execute_command(args);
			if (status == 127)
				fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
		}
	}
	return (status);
}
