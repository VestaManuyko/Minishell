/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:02:53 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 11:59:54 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_init.h"
#include <minishell.h>

void	free_shell(t_shell *sh)
{
	if (sh == NULL)
		return ;
	if (sh->cmd_line != NULL)
		free(sh->cmd_line);
	if (sh->env != NULL)
	{
		arr_free((char **)sh->env->arr);
		free(sh->env);
	}
	if (sh->items != NULL)
		free_progs(sh->items, sh->count);
	sh->items = NULL;
	sh = NULL;
}
