/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split_by_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 10:54:40 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/21 10:57:26 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	quote_val(char c)
{
	if (c == '"' || c == '\'')
		return ((int)c);
	return (0);
}

static char	*find_end(char *str, int quote)
{
	if (str == NULL)
		return (NULL);
	if (quote == 0)
	{
		while (*str && *str != '"' && *str != '\'')
			str++;
	}
	else
	{
		while (*str && *str != (char)quote)
			str++;
	}
	return (str);
}

t_arr	*str_split_by_quote(char *str)
{
	t_arr	*istr;
	char	*end;
	char	*line;
	int		quote;

	istr = tar_init(NULL, istr_free);
	if (istr == NULL)
		return (NULL);
	while (*str)
	{
		end = str;
		quote = quote_val(*str);
		end = find_end(str + (quote != 0), quote);
		line = ft_strncpy(str + (quote != 0), end - str - (quote != 0));
		if (line == NULL)
			return (NULL);
		if (!tar_putinfostr(istr, line, quote, 0))
			return (tar_free(istr), NULL);
		str = end + (quote != 0);
	}
	return (istr);
}
