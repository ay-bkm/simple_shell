#include "header.h"

/**
 * main - Entry point for the simple shell program.
 *
 * @argc: The number of command-line arguments (unused).
 * @argv: An array of strings containing the command-line arguments (unused).
 *
 * Return: Always returns 0 to indicate successful execution.
 */
int main(int argc, char **argv)
{
	int check_interactive;
	/* Suppress unused parameter warnings */
	(void)argc;
	(void)argv;

	check_interactive = isatty(STDIN_FILENO);
	/* Execute the interactive shell */
	if (check_interactive == 1)
	{
		execute_shell();
	}
	else
	{
		execute_shell_1();
	}
	return (0);
}
