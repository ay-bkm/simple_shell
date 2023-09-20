#include "header.h"
/**
 * main - entry
 * @ac: argument count
 * @av: argument vector
 * @env: environ
 * Return: status
*/
int main(int ac, char **av, char **env)
{
	int status;
	int check_interaction;
	(void)ac;
	(void)av;
	(void)env;


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
