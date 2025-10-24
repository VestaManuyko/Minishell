#include <minishell.h>

void	cmd_perror(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(ER_CMD, 2);
}
