/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_validate2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:40:49 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/17 12:40:53 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
