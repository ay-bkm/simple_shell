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
    size_t bufsize = 0;

    if (getline(cmd, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        {
            printf("\n");
            exit(0);
        }
        else
        {
            perror("getline failed");
            fprintf(stderr, "Error: Failed to read user input.\n");
            exit(1);
        }
    }
    (*cmd)[strcspn(*cmd, "\n")] = '\0';
    return (1);
}

/**
 * parse_input - Parse the input command into arguments.
 *
 * @input: The input command string to parse.
 * @args: An array to store the parsed arguments.
 * @max_args: The maximum number of arguments to store in 'args'.
 *
 * Return: 1 if successful, 0 on failure.
 */
int parse_input(char *input, char **args, int max_args)
{
	char *token = strtok(input, " ");
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
	printf("Exiting the shell...\n");
	exit(0);
}
