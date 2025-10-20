/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expand_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:50:13 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/20 18:17:43 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*save_substr(char *str, char **end, t_quote *data)
{
	char	*line;

	if (str + 1 <= *end || str + 1 == *end + 1 || *(*end + 1) == '\0')
	{
		if (*str == data->quote)
			str++;
		line = ft_strncpy(str, *end - str + 1);
		if (line == NULL)
			return (NULL);
		if (!tar_putstr(data->expand, line))
			return (NULL);
		free(line);
	}
	if (*(*end + 1) == data->quote && data->quote != '\0')
	{
		str = *end + 2;
		(*end)++;
		data->quote = str_isquoted(**end);
	}
	else
		str = *end + 1;
	return (str);
}

int	quotes(t_quote *data, char *str, int ign_quote)
{
	char	*end;

	(void)ign_quote;
	end = str;
	while (*str)
	{
		data->quote = str_isquoted(*end);
		if (*(end + 1) == data->quote
			/*|| (*(end + 1) == '$' && data->quote != '\'' )*/
			|| (data->quote == 0 && ft_strchr("\'\"", *(end + 1)) != NULL))
			str = save_substr(str, &end, data);
		if (str == NULL)
			return (0);
		end++;
	}
	return (1);
}
