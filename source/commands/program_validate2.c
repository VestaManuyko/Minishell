#include <minishell.h>

int	is_valid_file(char *exec)
{
	int			ret;
	struct stat	info;

	ret = stat(exec, &info);
	if (ret == -1)
		return (0);
	if (S_ISDIR(info.st_mode))
		return (0);
	if (!(S_ISREG(info.st_mode) || S_ISLNK(info.st_mode)))
		return (0);
	return (1);
}