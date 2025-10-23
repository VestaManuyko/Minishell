/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fillheredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:21:33 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 12:22:30 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmd_fillheredoc(t_red *tmp)
{
	char *path;

	// path = heredoc(tmp->raw, tmp->val);
	path = ft_strjoin("MISSING HEREDOC | pattern: ", tmp->val);
	if (path == NULL)
		return (0);
	free(tmp->val);
	tmp->val = path;
	return (1);
}
