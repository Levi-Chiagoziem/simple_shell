#include "main.h"

/**
  * _which - This Fn determines the appropriate path for an executable
  * @args: Array of arguments passed into the shell
  * @path_arr: A NULL-terminated arr of str containing the current PATHs
  * Return: Full path of executable.
  */
char *_which(char **args, char **path_arr)
{
	char *full_path = NULL, *tmp = NULL, *command = args[0];
	unsigned short i = 0, tmp_len = 0;
	unsigned int prev_size = 0;

	for (i = 0; path_arr[i]; i++)
	{
		tmp_len = _strlen(path_arr[i]) + _strlen(command) + 1;
		tmp = _realloc(tmp, prev_size, (sizeof(*tmp) * tmp_len));
		if (!tmp)
		{
			free_func(&tmp, 0);
			free_func(path_arr, -1);
			perror(tmp);
			return (NULL);
		}
		prev_size = sizeof(*tmp) * tmp_len;
		_strcpy(tmp, path_arr[i]);
		_strcat(tmp, command);

		if (access(tmp, F_OK) == 0)
		{
			full_path = tmp;
			free_func(path_arr, -1);
			return (full_path);
		}
	}
	free_func(path_arr, -1);
	free_func(&tmp, 0);
	return (NULL);
}

/**
  * custom_err - This Fn prints out a custom error message.
  * @cmd: The executable being run. First element of args array
  * @argv: A NULL-terminated arr of str passed into the CLI
  * @args: Array of arguments passed into the shell
  * @type: Type of error message to print.
 */
void custom_err(char *cmd, char **argv, char **args, int type)
{
	char *c_str = NULL, *e_msg = NULL, *tmp = NULL;

	c_str = digTostr(cmd_counter(0));
	if (type == 0)
		e_msg = concat_str(6, argv[0], ": ", c_str, ": ", cmd, ": not found\n");
	else if (type == 1)
	{
		tmp = concat_str(5, argv[0], ": ", c_str, ": ", cmd);
		e_msg = concat_str(4, tmp, ": Illegal number: ", args[1], "\n");
		free_func(&tmp, 0);
	}
	write(STDERR_FILENO, e_msg, _strlen(e_msg));
	free_func(&c_str, 0);
	free_func(&e_msg, 0);
}

/**
  * cmd_counter - This function counts the times the shell has executed cmds
  * @incr: Determines if Fn increments the value or just returns it
  * Return: The current value of counter.
  */

int cmd_counter(int incr)
{
	static int count;

	if (incr)
		count++;
	return (count);
}
