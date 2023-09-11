#include "header.h"

/**
 * get_user_input - Get user input from the command line.
 *
 * @cmd: The buffer to store the user input.
 *
 * Return: 1 if successful, 0 on failure.
 */
int get_user_input(char **cmd)
{
	size_t len = 0;
	ssize_t nread;

	nread = getline(cmd, &len, stdin);
	if (nread == -1)
	{
		if (feof(stdin))
		{
			write(1, "\n", 1);
			exit(0);
		}
		else
		{
			perror("getline failed");
			fprintf(stderr, "Error: Failed to read user input.\n");
			exit(1);
		}
	}
	(*cmd)[nread - 1] = '\0'; /* Remove newline character */
	return (1);
}

/**
 * handle_get_user_input_error - Handle errors during user input.
 */
void handle_get_user_input_error(void)
{
	fprintf(stderr, "Error: Failed to read user input.\n");
	exit(1);
}

/**
 * handle_parse_user_input_error - Handle errors during parsing user input.
 */
void handle_parse_user_input_error(void)
{
	fprintf(stderr, "Error: Failed to parse user input.\n");
	exit(1);
}

/**
 * handle_exit_command - Handle the "exit" command.
 */
void handle_exit_command(void)
{
	write(STDOUT_FILENO, "Exiting the shell...\n", 22);
	exit(0);
}
