#include "main.h"

/**
 * _myexit - function that exits the shell
 * @info: pzrmeter that stores potential arguments.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitstatus;

	if (info->argv[1])
	{
		exitstatus = _erratoi(info->argv[1]);
		if (exitstatus == -1)
		{
			info->status = 2;
			print_error(info, "Unknown status: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
