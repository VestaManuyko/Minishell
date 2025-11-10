/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 09:51:48 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 13:49:32 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	reset_shell(t_shell *sh)
{
	size_t	i;

	i = 0;
	if (sh == NULL)
		return ;
	if (sh->cmd_line != NULL)
		free(sh->cmd_line);
	sh->cmd_line = NULL;
	programs_free(sh->items, sh->count);
	if (sh->pipes != NULL)
	{
		while (i < (sh->count - 1))
			free(sh->pipes[i++]);
		free(sh->pipes);
		sh->pipes = NULL;
	}
	sh->items = NULL;
}
