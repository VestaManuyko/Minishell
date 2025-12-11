/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_valid_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:37:58 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/27 15:58:05 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_redirections.h"
#include <minishell.h>

int	cmd_valid_pipes(char *str, t_shell *sh)
{
	int	cmd_size;
	int	quotes;

	cmd_size = 0;
	quotes = 0;
	while (*str)
	{
		quotes = str_isquoted(*str);
		if ((*str == '|' || *str == '\n') && quotes == 0)
		{
			if (cmd_size == 0)
				return (red_perror(*str, sh), 0);
			cmd_size = 0;
		}
		if (!((*str == '|' || ft_strchr(MS_BLANKS, *str) != NULL)
				&& quotes == 0 && *str))
			cmd_size++;
		str++;
	}
	if (cmd_size == 0)
		return (red_perror(*str, sh), 0);
	return (1);
}
