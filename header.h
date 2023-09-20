#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>

#define BUFFER_SIZE 1024
extern char **environ;

int print_env(void);
char *_getenviron(const char *name);
char **split_array(char *buffer, int len_buffer);
char *check_path(char *cmd);
void handle_exit(char **arrays);
int execute_command(char **args);
int shell_non_interaction(void);
int shell_interactive(void);
void free_args(char **args);
int _strlen(const char *s);
char *_strchr(char *s, char c);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
char *_strdup(const char *src);




#endif
