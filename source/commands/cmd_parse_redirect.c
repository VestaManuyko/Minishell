/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_red.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:12:07 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/28 13:25:18 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_structs.h"
#include <minishell.h>

int	cmd_parse_red(t_arr *redirect, t_prog *proc, t_shell *sh, t_arr *cmds)
{
	int		i;
	t_red	*tmp;
	int		heredocs;

	(void)proc;
	heredocs = 0;
	i = 0;
	while (i < redirect->size)
	{
		tmp = (t_red *)redirect->arr[i];
		if (!red_raw2val(tmp, sh))
			return (0);
		if (tmp->type == in_heredoc)
			heredocs++;
		i++;
	}
	if (heredocs)
	{
		if (!handle_heredocs(sh, redirect, heredocs, cmds))
			return (0);
	}
	return (1);
}
