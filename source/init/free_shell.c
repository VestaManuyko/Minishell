/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:02:53 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/24 09:27:13 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_init.h"
#include "ms_strings.h"
#include <minishell.h>

void	free_shell(t_shell *sh)
{
	if (sh == NULL)
		return ;
	if (sh->cmd_line != NULL)
		free(sh->cmd_line);
	if (sh->env != NULL)
		tar_free(sh->env);
	if (sh->items != NULL)
		programs_free(sh->items, sh->count);
	sh->items = NULL;
	sh = NULL;
	rl_clear_history;
}
