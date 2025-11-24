/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expand_dollar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:50:13 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/11 15:43:13 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_strings.h"
#include <minishell.h>
#include <unistd.h>

static int	save_substr(char **str, char **end, t_quote *data)
{
	char	*line;

	if (*str > *end)
		return (0);
	line = ft_strncpy(*str, *end - *str + 1);
	if (line == NULL)
		return (0);
	if (!tar_putstr(data->expand, line))
		return (free(line), 0);
	free(line);
	*str = *end + 1;
	return (1);
}

static int	expand_dollar_special(char **str, char **end, t_quote *data)
{
	char	*line;

	line = NULL;
	if (*(*str + 1) == '$')
		line = ft_itoa(getpid());
	else
		line = ft_itoa(*data->status);
	if (line == NULL)
		return (0);
	if (!tar_putstr(data->expand, line))
		return (free(line), 0);
	free(line);
	(*end)++;
	*str = *str + 2;
	return (1);
}

static int	expand_dollar_envvar(char **str, char **end, t_quote *data)
{
	char	*key;
	char	*value;

	*end = *str + 1;
	while (*(*end + 1) && (ft_isalnum(*(*end + 1)) || *(*end + 1) == '_'))
		(*end)++;
	key = ft_strncpy(*str + 1, *end - *str);
	if (key == NULL)
		return (0);
	if (!env_getvalue((char **)data->env->arr, &value,
			env_getid((char **)data->env->arr, key)))
		return (0);
	if (value != NULL)
	{
		if (!tar_putstr(data->expand, value))
			return (free(key), free(value), 0);
		free(value);
	}
	else
		if (!tar_putstr(data->expand, ""))
			return (free(key), 0);
	free(key);
	*str = *end + 1;
	return (1);
}

static int	which_dollar_exp(char *str, int quote)
{
	if (*str == '$' && quote != '\'' && *(str + 1))
	{
		if (ft_strchr("?$", *(str + 1)) != NULL)
			return (1);
		else if (ft_isalnum(*(str + 1)) || *(str + 1) == '_')
			return (2);
	}
	return (0);
}

int	dollar(t_quote *data, char *str, int use_quote)
{
	char	*end;
	int		res;
	int		d_type;

	res = 1;
	end = str;
	while (*str)
	{
		data->quote = str_isquoted(*end) * use_quote;
		d_type = which_dollar_exp(str, data->quote);
		if (d_type == 1)
			res = expand_dollar_special(&str, &end, data);
		else if (d_type == 2)
			res = expand_dollar_envvar(&str, &end, data);
		else if (!(*(end + 1)) || (*(end + 1) == '$' && data->quote != '\''))
			res = save_substr(&str, &end, data);
		if (res == 0)
			return (0);
		end++;
	}
	return (1);
}
