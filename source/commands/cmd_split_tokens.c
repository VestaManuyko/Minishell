/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:18:08 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 12:20:50 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	extract_red(char **str, char **end, t_arr *tar, int *quotes)
{
	char *line;
	if ( **end == *(*end +1))
		(*end)++;
	while (**end && (*quotes == 0 && ft_isspace(*(*end + 1))))
	{
		(*end)++;
		*quotes = str_isquoted(**end);
	}
	while ((**end && *(*end + 1) != '\0') && ( *quotes != 0 
			|| (ft_strchr(MS_METACHAR, *(*end + 1)) == NULL
			&& ft_strchr(MS_BLANKS, *(*end + 1)) == NULL)))
	{
		(*end)++;
		*quotes = str_isquoted(**end);
	}
	line = ft_strncpy(*str, *end - *str + 1);
	if (line == NULL)
		return (0);
	if (!tar_putred(tar, line))
		return (free(line), 0);
	free(line);
	*str = *end + 1;
	return (1);		
}

int append_prog(char *str, char *end, t_arr *tar)
{
	char *line;

	line = ft_strncpy(str, end - str + 1);
	if (line == NULL)
		return (0);
	if (!tar_putstr(tar, line))
		return (free(line), 0);
	free(line);
	return (1);
}

int	cmd_split_tokens(t_prog *proc, char *str, t_arr *redirect)
{
	char	*end;
	int		quotes;
	int		res;
	
	end = str;
	res = 1;
	while (*str)
	{
		quotes = str_isquoted(*end);
		if (*end && ft_strchr(MS_BLANKS, *end) != NULL)
			str++;
		else if (*str && ft_strchr("<>", *str) != NULL && quotes == 0)
			res = extract_red(&str, &end, redirect, &quotes);
		else if (*(end + 1) == '\0' || (quotes == 0 && (
			ft_strchr(MS_METACHAR, *(end + 1)) || ft_strchr(MS_BLANKS, *(end + 1)))))
		{
			res = append_prog(str, end, proc->prog);
			str = end + 1;
		}
		if (res == 0)
			return (0);
		end++;
	}
	return (1);
}
