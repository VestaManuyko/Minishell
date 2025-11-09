/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmanuyko <vmanuyko@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:21:54 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/11/09 18:21:55 by vmanuyko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
 * Allocates memory for a 2d array of size nbr of commands - 1.
 * Then creates pipes and initialises the 2d array with piped fds.
 * Return value:
 * 0 on error, 1 on success.
*/
static int	create_pipes(t_shell *sh)
{
	int		**pipes;
	size_t	i;

	i = 0;
	pipes = malloc(sizeof(int *) * sh->count - 1);
	if (!pipes)
		return (0);
	while (i < sh->count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			
		}
	}
	return (1);
}

int	fork_children(t_shell *sh)
{
	if (!create_pipes(sh))
		return (0);
	return (1);
}