/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:59:49 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/17 18:59:50 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	cl_red_fds(t_shell *sh)
{
	int	i;

	i = 0;
	while (i < sh->count)
	{
		if (sh->items[i].redirect->size != 0)
		{
			if (sh->items[i].fd_io[0] != -1)
			{
				if (close(sh->items[i].fd_io[0]) == -1)
					return (perror(ER_CLOSE), 0);
				sh->items[i].fd_io[0] = -1;
			}
			if (sh->items[i].fd_io[1] != -1)
			{
				if (close(sh->items[i].fd_io[1]) == -1)
					return (perror(ER_CLOSE), 0);
				sh->items[i].fd_io[1] = -1;
			}
		}
		i++;
	}
	return (1);
}

int	close_fds(t_shell *sh)
{
	int	i;

	i = 0;
	if (!cl_red_fds(sh))
		return (0);
	while (i < (sh->count - 1))
	{
		if (sh->pipes[i][0] != -1)
		{
			if (close(sh->pipes[i][0]) == -1)
				return (perror(ER_CLOSE), 0);
		}
		if (sh->pipes[i][1] != -1)
		{
			if (close(sh->pipes[i][1]) == -1)
				return (perror(ER_CLOSE), 0);
		}
		sh->pipes[i][0] = -1;
		sh->pipes[i][1] = -1;
		i++;
	}
	return (1);
}
