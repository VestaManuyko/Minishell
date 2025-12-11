/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_elaborate_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:27:14 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/25 13:52:52 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	append_or_connect(t_arr *arr, char *str, int connect)
{
	char	*line;

	if (connect == 0 || arr->size == 0)
		return (tar_putstr(arr, str));
	else
	{
		line = ft_strjoin(arr->arr[arr->size - 1], str);
		if (line == NULL)
			return (0);
		free(arr->arr[arr->size - 1]);
		arr->arr[arr->size - 1] = line;
	}
	return (1);
}

static int	split_and_connect1st(t_arr *arr, t_istr *tmp)
{
	char	**tmparr;
	char	*line;
	int		i;

	tmparr = str_split_by_set(tmp->str, MS_BLANKS, 0);
	if (tmparr == NULL)
		return (0);
	if (arr->size > 0 && (tmp->connect == 1 || tmp->connect == 3))
	{
		line = ft_strjoin(arr->arr[arr->size - 1], tmparr[0]);
		if (line == NULL)
			return (arr_free(tmparr), 0);
		free(arr->arr[arr->size - 1]);
		arr->arr[arr->size - 1] = line;
	}
	i = (arr->size > 0 && (tmp->connect == 1 || tmp->connect == 3));
	while (tmparr[i] != NULL)
	{
		if (!tar_putstr(arr, tmparr[i]))
			return (arr_free(tmparr), 0);
		i++;
	}
	arr_free(tmparr);
	return (1);
}

static int	merge_by_connectivity(t_arr *arr, t_arr *istr)
{
	int		i;
	t_istr	*tmp;
	int		connect_last;

	i = 0;
	connect_last = 0;
	while (i < istr->size)
	{
		tmp = (t_istr *)istr->arr[i];
		if (tmp->type != 0)
		{
			if (!append_or_connect(arr, tmp->str, connect_last))
				return (0);
			connect_last = 1;
		}
		else if (tmp->str[0])
		{
			connect_last = (tmp->connect > 1);
			if (!split_and_connect1st(arr, tmp))
				return (0);
		}
		i++;
	}
	return (1);
}

t_arr	*cmd_elaborate_line(char *str, t_shell *sh)
{
	t_arr	*tar;
	t_arr	*istr;

	istr = str_split_by_quote(str);
	tar = tar_init(NULL, free);
	if (istr == NULL || tar == NULL)
		return (tar_free(istr), tar_free(tar), NULL);
	if (!istr_expand_var(istr, sh))
		return (tar_free(istr), NULL);
	if (!merge_by_connectivity(tar, istr))
		return (tar_free(tar), tar_free(istr), NULL);
	return (tar_free(istr), tar);
}
