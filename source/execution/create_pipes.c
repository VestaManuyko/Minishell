/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:34:55 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/10 12:34:56 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
/*
 * Initialises the pipes structure and fills up
 * the prog structures. 
 * Return value:
 * 0 on error, 1 on success.
*/
static int	init_pipes(t_shell *sh, int **pipes)
{
	size_t	i;

	i = 0;
	while (i < (sh->count - 1))
	{
		if (pipe(pipes[i]) == -1)
		{
			i = 0;
			while (i < (sh->count - 1))
				free(pipes[i++]);
			return (0);
		}
		sh->items[i].fd_io[0] = pipes[i][0];
		sh->items[i].fd_io[1] = pipes[i][1];
		i++;
	}
	return (1);
}

/*
 * Allocates memory for a 2d array of size nbr of commands - 1.
 * Then creates pipes and initialises the 2d array with piped fds.
 * Return value:
 * 0 on error, 1 on success.
*/
int	create_pipes(t_shell *sh)
{
	int		**pipes;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	pipes = malloc(sizeof(int *) * (sh->count - 1));
	if (!pipes)
		return (0);
	while (i < (sh->count - 1))
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			while (j < i)
				free(pipes[j++]);
			free(pipes);
		}
		i++;
	}
	if (!init_pipes(sh, pipes))
		return (free(pipes), 0);
	free(pipes);
	return (1);
}
