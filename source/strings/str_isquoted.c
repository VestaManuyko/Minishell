/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_isquoted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 09:12:23 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/03 11:29:49 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	str_isquoted(char c)
{
	static int quote = 0;
	if (c == '"' || c == '\'')
	{
		if (quote == 0)
			quote = (int)c;
		else if (quote == (int)c)
		{
			quote = 0;
	//		return ((int)c);
		}
			
	}
	return (quote);
}
