/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_validate2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:40:49 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/25 12:47:41 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_correct_error(char *exec)
{
	if (*exec == '\0')
		cmd_perror("", "''", ER_CMD);
	else
		cmd_perror("", exec, ER_CMD);
}

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
