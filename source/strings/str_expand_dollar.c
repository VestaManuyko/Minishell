/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expand_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:50:13 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/16 09:59:04 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*expand_dollar_special(char *str, char **end, t_quote *data)
{
	char	*line;

	line = ft_strdup("<< $$ and $? TO BE ADDED!!!>>");
	if (line == NULL)
		return (NULL);
	if (!tar_putone(data->expand, line))
		return (free(line), NULL);
	free(line);
	(*end)++;
	return (str + 2);
}

static char	*expand_dollar_envvar(char *str, char **end, t_quote *data)
{
	char	*key;
	char	*value;

	*end = str + 1;
	while (ft_isalnum(*(*end + 1)) && *(*end + 1) != '_')
		(*end)++;
	key = ft_strncpy(str + 1, *end - str);
	if (key == NULL)
		return (NULL);
	if (!env_getvalue(data->env->arr, &value, env_getid(data->env->arr, key)))
		return (NULL);
	if (value != NULL)
	{
		if (!tar_putone(data->expand, value))
			return (free(key), free(value), NULL);
	}
	free(key);
	if (value != NULL)
		free(value);
	if (*(*end + 1) == data->quote)
		str = *end + 2;
	else
		str = *end + 1;
	return (str);
}

int	dollar(t_quote *data, char *str)
{
	char	*end;

	end = str;
	while (*str)
	{
		data->quote = str_isquoted(*end);
		if (*str == '$' && data->quote != '\'')
		{
			if (ft_strchr("?$", *(str + 1)) != NULL)
				str = expand_dollar_special(str, &end, data);
			else if (ft_strchr("\'\"", *(str + 1)) != NULL
				|| ft_isspace(*(str + 1)))
				str++;
			else
				str = expand_dollar_envvar(str, &end, data);
		}
		if (str == NULL)
			return (0);
		end++;
	}
	return (1);
}
