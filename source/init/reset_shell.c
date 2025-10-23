/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 09:51:48 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 12:32:50 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void reset_shell(t_shell *sh)
{
	if (sh == NULL)
		return ;
	if (sh->cmd_line != NULL)
		free(sh->cmd_line);
	sh->cmd_line = NULL;
	programs_free(sh->items, sh->count);
	sh->items = NULL;
}
