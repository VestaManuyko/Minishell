/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:12:07 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 12:12:33 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int cmd_parse_redirect(t_arr *redirect, t_prog *proc, t_arr *env)
{
	int		i;
	t_red	*tmp;
	
	(void)proc;
	i = 0;
	while (i < redirect->size)
	{
		tmp = (t_red *)redirect->arr[i];
		if (!red_raw2val(tmp, env))
			return (0);
		if (tmp->type == in_heredoc)
			if (!cmd_fillheredoc(tmp))
				return (0);
		i++;
	}
	return (1);
}