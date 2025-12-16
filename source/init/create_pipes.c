/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:34:55 by vmanuyko          #+#    #+#             */
/*   Updated: 2025/12/16 13:59:52 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
/*
 * Initialises the pipes structure and fills up
 * the prog structures. 
 * Return value:
 * 0 on error, 1 on success.
*/
static int	init_pipes(t_shell *sh, int ***pipes)
{
	int	i;
	int j;

	i = 0;
	while (i < (sh->count - 1))
	{
		if (pipe((*pipes)[i]) == -1)
		{
			j = 0;
			while (j < i)
			{
				close((*pipes)[j][0]);
                close((*pipes)[j][1]);
				j++;
			}
			j = 0;
			while (j < sh->count - 1)
				free((*pipes)[j++]);
			free (*pipes);
			*pipes = NULL;
			return (0);
		}
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
	int	i;
	int	j;

	i = 0;
	j = 0;
	sh->pipes = malloc(sizeof(int *) * (sh->count - 1));
	if (!sh->pipes)
		return (sh->status = 1, 0);
	while (i < (sh->count - 1))
	{
		sh->pipes[i] = malloc(sizeof(int) * 2);
		if (!sh->pipes[i])
		{
			while (j < i)
				free(sh->pipes[j++]);
			free(sh->pipes);
			sh->pipes = NULL;
		}
		i++;
	}
	if (!init_pipes(sh, &sh->pipes))
		return (sh->status = 1, 0);
	return (1);
}
