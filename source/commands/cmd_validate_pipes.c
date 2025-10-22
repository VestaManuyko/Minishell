/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validate_pipes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:37:58 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/22 15:38:54 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int cmd_validate_pipes(char *str)
{
	int cmd_done = 0;
	int cmd_size = 0;
	
	while (*str)
	{
		if (*str == '|' || *str == '\n')
			cmd_done = 1;
		if (cmd_done == 1)
		{
			if (cmd_size == 0)
				return (0);
			cmd_done = cmd_size = 0;
		}
		if (*str && *str != '|' && ft_strchr(MS_BLANKS, *str) == NULL)
			cmd_size++;
	}	
	return (1);	
}
