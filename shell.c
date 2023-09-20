#include "header.h"

/**
 * execute_command - Executes a command specified by the args array.
 * @args: The array containing the command and its arguments.
 * Return: The exit status of the executed command.
 */
int execute_command(char **args)
{
    pid_t pid;
    char *command;
    int status;
    int exit_status;

    /* Check if the command is empty or consists of only whitespace characters */
    int i;
    for (i = 0; args[i] != NULL; i++)
    {
        if (args[i][0] != '\0' && !isspace(args[i][0]))
            break;
    }

    if (args[i] == NULL)
        return 0; /* Return 0 for empty or whitespace-only commands */

    pid = fork();
    if (pid == 0)
    {
        if (access(args[0], F_OK) == 0)
            execve(args[0], args, environ);
        else
        {
            command = check_path(args[0]);
            if (command)
            {
                execve(command, args, environ);
            }
            else
            {
                /* Check if the command contains a pipe symbol */
                if (strchr(args[0], '|') != NULL)
                {
                    fprintf(stderr, "./hsh: 1: %s: invalid use of pipe\n", args[0]);
                    exit(127);  /* Exit with an error status */
                }
                else
                {
                    fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
                    exit(127);
                }
            }
        }
    }
    else if (pid < 0)
    {
        perror("fork");
    }
    else
    {
        wait(&status);
        if (WIFEXITED(status))
        {
            exit_status = WEXITSTATUS(status);
            return (exit_status);
        }
    }
    return (0);
}



int shell_interactive(void)
{
    char **args, *buf = NULL;
    size_t size = 0;
    int n, status, i, is_empty;

    while (printf("#cisfun$ "), n = getline(&buf, &size, stdin), n != -1)
    {
        if (n > 1 && buf[n - 1] == '\n')
            buf[--n] = 0;
        is_empty = 1;

        for (i = 0; i < n; i++)
            if (buf[i] != ' ')
                is_empty = 0;
        if (is_empty)
            continue;
        args = split_array(buf, n);
        if (_strcmp(args[0], "env") == 0)
            status = print_env();
        else if (_strcmp(args[0], "exit") == 0)
            free(buf), handle_exit(args);
        else
        {
            status = execute_command(args);
            if (status == 127)
                fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
        }
        free_args(args);
        free(buf);
        buf = NULL;
        size = 0;
    }
    if (n == -1 && feof(stdin))
        printf("\n"), free(buf), exit(status);
    perror("getline failed");
    exit(1);
}

int shell_non_interaction(void)
{
    char *line = NULL;
    int status;
    size_t size = 0;
    char **args = NULL;

    while (getline(&line, &size, stdin) > 0)
    {
        args = split_array(line, _strlen(line));
        if (_strcmp(args[0], "exit") == 0)
            handle_exit(args);
        if (_strcmp(args[0], "env") == 0)
            status = print_env();
        else
        {
            status = execute_command(args);
            if (status == 127)
                fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
        }
        free(line);
        line = NULL;
        size = 0;
    }
    return (status);
}
