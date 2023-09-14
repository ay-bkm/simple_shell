#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_CMD_LEN 1024
#define MAX_ARG_LEN 256
extern char **environ;

int get_user_input(char **cmd);
int parse_user_input(const char *input, char **args, int max_args);
void execute_command(char *args[]);
void execute_shell(void);
void execute_env(void);

void handle_get_user_input_error(void);
void handle_parse_user_input_error(void);
void handle_exit_command(void);

char *get_command(char *command);
char *_getenviron(char *name);
char **split_array(char *buffer);
void execute_shell_1(void);


#endif /* HEADER_H */
