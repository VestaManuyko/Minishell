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

/*
 * Closes fds for redirections.
*/
void	cl_red_fds(t_shell *sh)
{
	int	i;

	i = 0;
	while (i < sh->count)
	{
		if (sh->items[i].redirect->size != 0)
		{
			if (sh->items[i].fd_io[0] > 1)
			{
				close(sh->items[i].fd_io[0]);
				sh->items[i].fd_io[0] = -1;
			}
			if (sh->items[i].fd_io[1] > 1)
			{
				close(sh->items[i].fd_io[1]);
				sh->items[i].fd_io[1] = -1;
			}
		}
		i++;
	}
}

/*
 * Close all opened fds.
*/
void	close_fds(t_shell *sh)
{
	int	i;

	i = 0;
	cl_red_fds(sh);
	while (i < (sh->count - 1))
	{
		if (sh->pipes[i][0] > 1)
			close(sh->pipes[i][0]);
		if (sh->pipes[i][1] > 1)
			close(sh->pipes[i][1]);
		sh->pipes[i][0] = -1;
		sh->pipes[i][1] = -1;
		i++;
	}
}

/*
 * Called from a child process to close all unused fds by that process.
*/
void	close_unused_fds(t_prog *item, t_shell *sh)
{
	int	i;

	i = 0;
	while (i < (sh->count - 1))
	{
		if (i != (item->id - 1) && sh->pipes[i][0] != -1)
		{
			close(sh->pipes[i][0]);
			sh->pipes[i][0] = -1;
		}
		if (i != item->id && sh->pipes[i][1] != -1)
		{
			close(sh->pipes[i][1]);
			sh->pipes[i][1] = -1;
		}
		i++;
	}
}
