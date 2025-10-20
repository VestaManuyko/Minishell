/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_str2struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 02:55:10 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/20 13:10:02 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <minishell.h>

t_redtype	red_settype(char *str)
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
		type = error;
	return (type);
}

char *string_start(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_strchr(MS_BLANKS, str[i]) != NULL)
		i++;
	if (ft_strchr(MS_METACHAR, str[i]) != NULL)
		return (red_perror(str[i]), NULL);
	return (&str[i]);
}

char *extract_value(t_red *item, char *str)
{
	char		*start;
	char		*tmp;

	start = NULL;
	if (item->type == in_heredoc || item->type == out_append)
		start = string_start(str + 2);
	else
		start = string_start(str + 1);
	if (start == NULL)
		return (NULL);
	tmp = ft_strdup(start);
	return (tmp);

}

t_red *red_str2struct(char *str)
{
	t_red		*item;

	item = red_init(red_settype(str), NULL);
	if (item == NULL)
		return (NULL);
	if (item->type == error)
		return  (NULL);
	item->raw = extract_value(item, str);
	if (item->raw == NULL) 
		return (free(item), NULL);
	return (item);
}		
