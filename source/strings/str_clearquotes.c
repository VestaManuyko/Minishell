/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_clearquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:36:25 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/07 16:01:16 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *str_clearquotes(char *str)
{
	int i;
	int expansions;
	int quotes;

	i = 0;
	expansions = 0;
	quotes = 0;
	while (str[i] != '\0')
	{
		quotes = str_isquoted(str[i]);
		if (str[i] == '$' && quotes != '\'')
		{
			expansions++;
			i++;
			if ((str[i] == '?' || str[i] == '$') && str[i + 1] != 0)
				expansion++;
			while (str[i] != ' ')
			{
				if (str[i] == 0)
					break ;
				i++;
			}
			expansion++;
		}
		i++;

	}
}
