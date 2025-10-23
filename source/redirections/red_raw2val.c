/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_raw2val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:19:46 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/21 16:21:26 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	red_raw2val(t_red *item, t_arr *env)
{
	char	*line_d;
	char	*line_q;

	if (item->type != in_heredoc)
	{
		line_d = str_expand(dollar, env, item->raw, 1);
		if (line_d == NULL)
			return (0);
	}
	else
		line_d = item->raw;
	line_q = str_expand(quotes, env, line_d, 0);
	if (item->type != in_heredoc)
		free(line_d);
	if (line_q == NULL)
		return (0);
	item->val = line_q;
	return (1);
}
