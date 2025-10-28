/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fillheredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:21:33 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/28 13:28:57 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_structs.h"
#include <minishell.h>

int	cmd_fillheredoc(t_red *tmp, t_arr *env)
{
	char	*path;

	path = heredoc(tmp->raw, tmp->val, env);
	if (path == NULL)
		return (0);
	free(tmp->val);
	tmp->val = path;
	return (1);
}
