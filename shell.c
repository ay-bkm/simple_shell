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
	/* Suppress unused parameter warnings */
	(void)argc;
	(void)argv;

	/* Execute the interactive shell */
	execute_shell();
	return (0);
}
