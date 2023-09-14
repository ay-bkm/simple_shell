#include "header.h"

/**
 * main - Entry point for the simple shell program.
 *
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 *
 * Return: 0 on success, or an error code on failure.
 */
int main(int argc, char **argv)
{
	/* Suppress unused parameter warnings */
	(void)argc;
	(void)argv;
	/* Check if interactive mode */
	if (isatty(STDIN_FILENO))
	{
		execute_shell(); /* Interactive mode */
	} else
	{
		/* Non-interactive mode */
		char *args[MAX_ARG_LEN], *cmd = NULL;
		int result;

		while (1) /* Read commands from redirected input or script */
		{
			result = get_user_input(&cmd);
			if (result == 0) /* Check for end of input */
				break;
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
			} else if (strcmp(args[0], "env") == 0)
			{
				execute_env();
			} else
			{
				execute_command(args);
			}
		}
	}

	return (0);
}
