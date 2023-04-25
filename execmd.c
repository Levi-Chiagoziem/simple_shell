#include "main.h"
#include <errno.h>

extern int cmd_count;

char *_getenv(char *env_name)
{
        extern char **environ;
        int i = 0;
        char *value = NULL;


        while(environ[i])
        {
                if(strncmp(environ[i], env_name, strlen(env_name)) == 0)
                {
                        value = environ[i] + strlen(env_name);
                        break;
                }
                i++;
        }
        return (value);
}

char **get_PATH(void)
{
        char *path = NULL;
        char **path_arr = NULL;

        path = _getenv("PATH");
        if (path)
                path_arr = split_string(path, ":");
        return (path_arr);
}

short int create_process(char **args, char **env)
{
	pid_t child_pid;
	int wStatus;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (child_pid == 0)
	{
		/*Code will be executed by child */
		execve(args[0], args, env);
		/*Execve shouldn't return here. If it does, it must have failed*/
		perror(args[0]);
	}

	else
	{
		/*This code is run by parent process, Wait for child to terminate*/
		if (waitpid(child_pid, &wStatus, 0) == -1)
		{
			perror("waitpid");
			return (-1);
		}
	}
	return (0);
}


char *concat_str(const unsigned int n, ...)
{
	va_list str_list;
	char *str = NULL, *new_str = NULL;
	unsigned int i = 0, tot_len = 0;

	va_start(str_list, n);
	while (i < n)
	{
		str = va_arg(str_list, char *);
		tot_len += strlen(str);
		new_str = realloc(new_str, (sizeof(*new_str) * (tot_len + 1)));

		if (!new_str)
		{
			free_func(&new_str, 0);
			perror("concat_str function");
			return (NULL);
		}
		if (i == 0)
			new_str = strcpy(new_str, str);
		else
			strcat(new_str, str);

		i++;;
	}
	va_end(str_list);
	return (new_str);
}

char *_which(char **args, char **path_arr)
{
	char *full_path = NULL, *tmp = NULL, *command = args[0];
	unsigned short i = 0, tmp_len = 0;

	for (i = 0; path_arr[i]; i++)
	{
		tmp_len = strlen(path_arr[i]) + strlen(command) + 1;
		tmp = realloc(tmp, (sizeof(*tmp) * tmp_len));
		
		if (!tmp)
		{
			free_func(&tmp, 0);
			free_func(path_arr, -1);
			perror(tmp);
			return (NULL);
		}

		strcpy(tmp, path_arr[i]);
		strcat(tmp, command);
		
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


void execmd(char**argv, char **args)
{
	extern int errno;
	extern char **environ;
	char *command = NULL, *err_msg = NULL, **path_arr = NULL, *full_path = NULL;
	unsigned short process_code = 0;
	char *cmd_count_str = NULL;

	command = args[0];
	if (access(command, F_OK) == 0)
	{
		process_code = create_process(args, environ);
		return;
	}
	else if (strchr(command, '/') != NULL)
	{
		errno = ENOENT;
		err_msg = concat_str(3, argv[0], ": ", command);
		perror(err_msg);
		/*set exit code to 127*/
	}
	else
	{
		path_arr = get_PATH();
		full_path = _which(args, path_arr);
		if (full_path)
		{
			free_func(&args[0], 0);
			args[0] = full_path;
			process_code = create_process(args, environ);
		}
		
		else
		{
			cmd_count_str = digTostr(cmd_count); 
			err_msg = concat_str (6, argv[0], ": ", cmd_count_str,": " , command, ": not found\n");
			write(STDERR_FILENO, err_msg, strlen(err_msg));
			free_func(&cmd_count_str, 0);
			/*set exit code to 127*/

		}
	}
	free_func(&err_msg, 0);
	process_code = process_code;
}
