/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:18:08 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/27 15:56:37 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_structs.h"
#include "ms_structs_support.h"
#include <minishell.h>

char	set_next_char(char c, t_pipe status)
{
	if ((c == '\0' || c == '\n') && status == ispipe)
		return ('|');
	if (c == '\0')
		return ('\n');
	return (c);
}

static int	extract_red(char **str, char **end, t_arr *tar, t_reder *d)
{
	char	*line;

	if (**end == *(*end +1))
		(*end)++;
	while (**end && (d->quotes == 0 && ft_isspace(*(*end + 1))))
	{
		(*end)++;
		d->quotes = str_isquoted(**end);
	}
	while ((**end && *(*end + 1) != '\0') && (d->quotes != 0
			|| (ft_strchr(MS_METACHAR, *(*end + 1)) == NULL
				&& ft_strchr(MS_BLANKS, *(*end + 1)) == NULL)))
	{
		(*end)++;
		d->quotes = str_isquoted(**end);
	}
	line = ft_strncpy(*str, *end - *str + 1);
	if (line == NULL)
		return (0);
	if (!tar_putred(tar, line, set_next_char(*(*end + 1), d->proctype), d))
		return (free(line), 0);
	free(line);
	*str = *end + 1;
	return (1);
}

static int	append_prog(char *str, char *end, t_arr *tar)
{
	char	*line;

	line = ft_strncpy(str, end - str + 1);
	if (line == NULL)
		return (0);
	if (!tar_putstr(tar, line))
		return (free(line), 0);
	free(line);
	return (1);
}

void set_reder(t_reder *d, t_prog *proc, t_shell *sh)
{
	d->res = 1;
	d->proctype = proc->go_to;
	d->sh = sh;
}
int	cmd_split_tokens(t_prog *proc, char *str, t_arr *redirect, t_shell *sh)
{
	char	*end;
	t_reder	d;

	end = str;
	set_reder(&d, proc, sh);
	while (*str)
	{
		d.quotes = str_isquoted(*end);
		if (*end && d.quotes == 0 && ft_strchr(MS_BLANKS, *end) != NULL)
			str++;
		else if (*str && ft_strchr("<>", *str) != NULL && d.quotes == 0)
			d.res = extract_red(&str, &end, redirect, &d);
		else if (*(end + 1) == '\0' || (d.quotes == 0 && (
					ft_strchr(MS_METACHAR, *(end + 1))
					|| ft_strchr(MS_BLANKS, *(end + 1)))))
		{
			d.res = append_prog(str, end, proc->prog);
			str = end + 1;
		}
		if (d.res == 0)
			return (0);
		end++;
	}
	return (0);
}
