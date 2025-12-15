/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:02:53 by fpaglia           #+#    #+#             */
/*   Updated: 2025/12/15 16:59:42 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_shell(t_shell *sh)
{
	int	i;

	i = 0;
	if (sh == NULL)
		return ;
	if (sh->cmd_line != NULL)
		free(sh->cmd_line);
	if (sh->env != NULL)
		tar_free(sh->env);
	if (sh->items != NULL)
		programs_free(sh->items, sh->count);
	sh->items = NULL;
	if (sh->pipes != NULL)
	{
		while (i < (sh->count - 1))
			free(sh->pipes[i++]);
		free(sh->pipes);
		sh->pipes = NULL;
	}
	sh = NULL;
	rl_clear_history();
}
