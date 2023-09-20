#include "header.h"
/**
 * main - entry
 * @ac: argument count
 * @av: argument vector
 * Return: status
*/
int main(int ac, char **av)
{
	int status;
	int check_interaction;
	(void)ac;
	(void)av;


	check_interaction = isatty(STDIN_FILENO);
	if (check_interaction)
	{
		status = shell_interactive();
	}
	else
	{
		status = shell_non_interaction();
	}
	return (status);
}
