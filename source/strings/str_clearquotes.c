/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_clearquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:36:25 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/09 13:14:57 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clearquotes.h"
#include <minishell.h>

static char	*expand_dollar_special(char *str, char **end, t_quote *data)
{
	char	*line;

	line = ft_strdup("<< $$ and $? TO BE ADDED!!!>>");
	if (line == NULL)
		return (NULL);
	if (tar_putone(data->expand, line) == -1)
		return (free(line), NULL);
	free(line);
	(*end)++;
	return (str + 2);
}

static char	*expand_dollar_envvar(char *str, char **end, t_quote *data)
{
	char	*line;
	char	*line2;

	*end = str + 1;
	while (!ft_strchr("\'\"", *(*end + 1)) && !ft_isspace(*(*end + 1)))
		(*end)++;
	line = ft_strncpy(str + 1, *end - str);
	if (line == NULL)
		return (NULL);
	line2 = env_getvalue(data->env->arr, env_getid(data->env->arr, line));
	if (line2 != NULL)
	{
		if (tar_putone(data->expand, line2) == -1)
			return (free(line), free(line2), NULL);
	}
	free(line);
	if (line2 != NULL)
		free(line2);
	if (data->quote != 0)
		str = *end + 2;
	else
		str = *end + 1;
	return (str);
}

static char	*save_substr(char *str, char *end, int quotes, t_arr *expand)
{
	char	*line;

	if (str + 1 < end || str + 1 == end + 1)
	{
		if (*str == quotes)
			str++;
		line = ft_strncpy(str, end - str + 1);
		if (line == NULL)
			return (NULL);
		tar_putone(expand, line);
		free(line);
	}
	if (*(end + 1) == quotes && quotes != '\0')
		str = end + 2;
	else
		str = end + 1;
	return (str);
}

static int	build_arr(t_quote *data, char *str)
{
	char	*end;

	data->quote = 0;
	end = str;
	while (*str)
	{
		data->quote = str_isquoted(*end);
		if (*str == '$' && data->quote != '\'')
		{
			if (ft_strchr("?$", *(str + 1)) != NULL)
				str = expand_dollar_special(str, &end, data);
			else
				str = expand_dollar_envvar(str, &end, data);
		}
		else if (*(end + 1) == data->quote
			|| (*(end + 1) == '$' && data->quote != '\'' )
			|| (data->quote == 0 && ft_strchr("\'\"", *(end + 1)) != NULL))
			str = save_substr(str, end, data->quote, data->expand);
		if (str == NULL)
			return (0);
		end++;
	}
	return (1);
}

char	*str_clearquotes(t_arr *env, char *str)
{
	char	*line;
	t_quote	data;

	line = NULL;
	data.expand = tar_init(NULL);
	data.env = env;
	if (data.expand == NULL)
		return (NULL);
	if (!build_arr(&data, str))
		return (arr_free(data.expand->arr), free(data.expand), NULL);
	line = arr_to_str(data.expand->arr);
	if (line == NULL)
		return (arr_free(data.expand->arr), free(data.expand), NULL);
	free(data.expand);
	return (line);
}
