#ifndef _MAIN_H_
#define _MAIN_H_

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

extern int errno;
extern char **environ;

/**
  * struct built_in - A structure keeping track of built-ins
  * @exe: Name of built_in
  * @func: Function to handle built-in
  */
typedef struct built_in
{
	char *exe;
	int (*func)(char **args, char **env);
} built_in;

/**
  * struct Node - A structure keeping track of env nodes
  * @name: Name of Node
  * @value: Value of Node
  * @next: Pointer to next node
  */
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


char *_strchr(char *s, char c);
int _strlen(const char *s);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, size_t n);
char *_strncat(char *dest, char *src, int n);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *s);
int count_digits(long num, long base);

int exit_shell(char **args, char **env, char **, char **);
int print_env(char **args, char **env);
int check_builtin(char **args, char **envs, char **, char **);
int set_env(char **args, char **env);
int unset_env(char **args, char **env);
char *_getenv(char *env_name);
void print_node(Node *ptr);
Node *getenv_list(char **environ);
void free_node(Node *ptr);
char *_strtok(char *str, const char *delim);
ssize_t _getline(char **lineptr, size_t *n, int fd);
void free_linked_list(Node *ptr);
int cmd_counter(int incr);
void custom_err(char *command, char **argv, char **, int);
char *_which(char **args, char **path_arr);
char *concat_str(const unsigned int n, ...);
char *_strncpy(char *dest, char *src, int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void *_memcpy(void *dest, void *src, unsigned int n);
int _atoi_cust(char *s);

#endif /** MAIN_H */
