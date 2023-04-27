#include <main.h>

/**
 * _myhelp - changes the current directory of the process
 * @info: parameter that containing potential arguments
 *  Return: return 0 when successful
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("the help call function  works. not fully though\n");
	if (0)
		_puts(*arg_array);
	return (0);
}

/**
 * _mycd - function that changes the current directory of the process
 * @info: paremter that  containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *s, *directory;
	char buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (s == NULL)
		_puts("TODO: >>getcwd failed\n");
	if (!info->argv[1])
	{
		directory = _getenv(info, "HOME=");
		if (directory == NULL)
			chdir_ret = chdir((directory = _getenv(info, "PWD=")) ? directory : "/");
		else
			chdir_ret = chdir(directory);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((directory = _getenv(info, "OLDPWD=")) ? directory : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd into ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
