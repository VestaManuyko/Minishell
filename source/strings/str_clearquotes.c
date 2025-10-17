/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_clearquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:36:25 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/17 17:27:15 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_strings.h"
#include <minishell.h>

char	*str_clearquotes(t_arr *env, char *str)
{
	char	*line;
	char	*line2;

	line = str_expand(dollar, env, str);
	if (line == NULL)
		return (NULL);
	line2 = str_expand(quotes, env, line);
	if (line2 == NULL)
		return (free(line), NULL);
	free(line);
	return (line2);
}
