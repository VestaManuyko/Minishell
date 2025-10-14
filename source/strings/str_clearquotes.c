/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_clearquotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:36:25 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/14 13:28:55 by fpaglia          ###   ########.fr       */
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
	while (*(*end + 1) && (ft_isalnum(*(*end + 1)) || *(*end + 1) == '_'))
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
	if (*(*end + 1) != '\0' && *(*end + 1) == data->quote)
		str = *end + 2;
	else
		str = *end + 1;
	return (str);
}

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
		if (!tar_putone(data->expand, line))
			return (free(line), NULL);
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

static int	build_arr(t_quote *data, char *str)
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
		else if (*(end + 1) == data->quote
			|| (*(end + 1) == '$' && data->quote != '\'' )
			|| (data->quote == 0 && ft_strchr("\'\"", *(end + 1)) != NULL))
			str = save_substr(str, &end, data);
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

	if (!str)
		return (NULL);
	if (*str == '\0')
		return (ft_strdup(""));
	line = NULL;
	data.expand = tar_init(NULL);
	data.env = env;
	data.quote = 0;
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
