/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_str2struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 02:55:10 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/26 11:57:43 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_redtype	red_settype(char *str)
{
	t_redtype	type;

	if (str[0] == '<' && str[1] == '<')
		type = in_heredoc;
	else if (str[0] == '<' && str[1] != '<')
		type = in_file;
	else if (str[0] == '>' && str[1] == '>')
		type = out_append;
	else if (str[0] == '>' && str[1] != '>')
		type = out_create;
	else
		type = none;
	return (type);
}

static char	*string_start(char *str, char next)
{
	int	i;

	i = 0;
	while (str[i] && ft_strchr(MS_BLANKS, str[i]) != NULL)
		i++;
	if (ft_strchr(MS_METACHAR, str[i]) != NULL)
		return (red_perror(next), NULL);
	return (&str[i]);
}

static char	*extract_value(t_red *item, char *str, char next)
{
	char		*start;
	char		*tmp;

	start = NULL;
	if (item->type == in_heredoc || item->type == out_append)
		start = string_start(str + 2, next);
	else
		start = string_start(str + 1, next);
	if (start == NULL)
		return (NULL);
	tmp = ft_strdup(start);
	return (tmp);
}

t_red	*red_str2struct(char *str, char next)
{
	t_red		*item;

	item = red_init(red_settype(str), NULL);
	if (item == NULL)
		return (NULL);
	if (item->type == none)
		return (NULL);
	item->raw = extract_value(item, str, next);
	if (item->raw == NULL)
		return (free(item), NULL);
	return (item);
}
