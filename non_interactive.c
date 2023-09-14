#include "header.h"
/**
 * execute_shell_1 - function that handle
 * non interactive mode
*/
void execute_shell_1(void)
{
	char *line = NULL;
	size_t size = 0;
	char **args = NULL;

	while (getline(&line, &size, stdin) > 0)
	{
		args = split_array(line);
		if (strcmp(args[0], "exit") == 0)
			handle_exit_command();
		if (strcmp(args[0], "env") == 0)
			execute_env();
		else
			execute_command(args);
	}
	free(line);
	free(args);
}
