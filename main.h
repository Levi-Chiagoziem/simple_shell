#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
/**
 * function_name - brief description of what the function does
 * @arg1: description of the first argument
 * @arg2: description of the second argument
 *
 * Return: description of the return value
 */

typedef struct built_in
{
	char *exe;
	int (*func)(char **args, char **env);
} built_in;

typedef struct Node
{
	char *name;
	char *value;
	struct Node *next;
} Node;

void free_func(char **ptr, int length);
extern int cmd_count;
void execmd(char **argv, char **args);
char **split_string(char *str, char *delim);
char **get_PATH(void);
char *digTostr(long num);
char **tokens_to_arr(char *command_copy, int num_tokens, const char *delim);
char **line_to_args(char *command, const char *delim);
int exit_shell(char **args, char **env);
int print_env(char **args, char **env);
int check_builtin(char **args);
int set_env(char **args, char **env);
int unset_env(char **args, char **env);
char *_getenv(char *env_name);
void print_node(Node *ptr);
Node *getenv_list(void);
void free_node(Node *ptr);
int count_digits(long num, long base);
#endif /** MAIN_H */

