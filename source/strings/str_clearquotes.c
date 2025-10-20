/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_clearquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:36:25 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/20 18:29:49 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_strings.h"
#include <minishell.h>

char	*str_clearquotes(t_arr *env, char *str, int ign_quote)
{
	char	*line;
	char	*line2;

	line = str_expand(dollar, env, str, ign_quote);
	if (line == NULL)
		return (NULL);
	line2 = str_expand(quotes, env, line, ign_quote);
	if (line2 == NULL)
		return (free(line), NULL);
	free(line);
	return (line2);
}
