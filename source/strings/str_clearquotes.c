/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_clearquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:36:25 by fpaglia           #+#    #+#             */
/*   Updated: 2025/12/15 17:00:26 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*str_clearquotes(char *str, int use_quote, t_shell *sh)
{
	char	*line;
	char	*line2;

	line = str_expand(dollar, str, use_quote, sh);
	if (line == NULL)
		return (NULL);
	line2 = str_expand(quotes, line, use_quote, sh);
	if (line2 == NULL)
		return (free(line), NULL);
	free(line);
	return (line2);
}
