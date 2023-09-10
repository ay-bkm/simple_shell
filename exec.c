#include "header.h"

/**
 * parse_user_input - Parse user input into arguments.
 *
 * @input: The user input string.
 * @args: The array to store parsed arguments.
 * @max_args: The maximum number of arguments.
 *
 * Return: 1 if successful, 0 on failure.
 */
int parse_user_input(const char *input, char **args, int max_args)
{
	char *token = strtok((char *)input, " ");
	int i = 0;

	while (token != NULL && i < max_args - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}

	args[i] = NULL;

	return (1);
}

/**
 * execute_command - Execute a command with its arguments.
 *
 * @args: Array of command arguments, where the first element is the command.
 */
void execute_command(char *args[])
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror(args[0]);
			exit(127); /* Exit with the same error code as sh */
		}
	}
	else if (pid > 0)
	{
		wait(&status);
	}
	else
	{
		perror("fork failed");
		exit(1); /* Exit with an error code */
	}
}

/**
 * execute_shell - Execute the interactive shell.
 */
void execute_shell(void)
{
	char *cmd = NULL;
	char *args[MAX_ARG_LEN];

	while (1)
	{
		printf("#cisfun$ ");
		if (!get_user_input(&cmd))
		{
			handle_get_user_input_error();
			continue;
		}

		if (!parse_user_input(cmd, args, MAX_ARG_LEN))
		{
			handle_parse_user_input_error();
			continue;
		}

		if (args[0] == NULL)
			continue;

		if (strcmp(args[0], "exit") == 0)
		{
			handle_exit_command();
		}
		else if (strcmp(args[0], "env") == 0)
		{
			execute_env();
		}
		else
		{
			execute_command(args);
		}
	}
}

/**
 * execute_env - Execute the "env" built-in command.
 */
void execute_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
