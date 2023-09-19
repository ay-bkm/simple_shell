#include "header.h"
/**
 * main - entry
 * Return: status
*/
int main(void)
{
	int status;
	int check_interaction;

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
