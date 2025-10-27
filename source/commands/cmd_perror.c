#include "err_mes.h"
#include "libft.h"
#include <minishell.h>

void	cmd_perror(char *pre, char *str, char *err)
{
	ft_putstr_fd(pre, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
}
