/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:29:24 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/25 13:53:02 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	merge_istr(t_arr *arr, t_arr *istr)
{
	int		i;
	t_istr	*tmp;
	char	*str;
	char	*line;

	i = 0;
	str = NULL;
	while (i < istr->size)
	{
		line = str;
		tmp = (t_istr *)istr->arr[i];
		if (str == NULL)
			str = ft_strdup(tmp->str);
		else
			str = ft_strjoin(line, tmp->str);
		if (str == NULL)
			return (0);
		free(line);
		i++;
	}
	if (!tar_putstr(arr, str))
		return (free(str), 0);
	return (free(str), 1);
}

/* This function equals the cmd_elaborate line with the sole
 * exception of the merging method everything comes back to
 * one string 
 */
static t_arr	*expand_line(char *str, t_shell *sh)
{
	t_arr	*tar;
	t_arr	*istr;

	istr = str_split_by_quote(str);
	tar = tar_init(NULL, free);
	if (istr == NULL || tar == NULL)
		return (tar_free(istr), tar_free(tar), NULL);
	if (!istr_expand_var(istr, sh))
		return (tar_free(istr), NULL);
	if (!merge_istr(tar, istr))
		return (tar_free(tar), tar_free(istr), NULL);
	return (tar_free(istr), tar);
}

/* Evaluates if the key includes any variable or quote
 * Special case for the export functionality.
 */
static int	quotes_or_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (str[i] == '"' || str[i] == '\'' || str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

t_arr	*cmd_expand_export(t_arr *arr, t_shell *sh)
{
	t_arr	*tar;
	t_arr	*tmp;
	int		i;

	tar = tar_init(NULL, free);
	if (tar == NULL)
		return (NULL);
	i = 0;
	while (i < arr->size)
	{
		if (!quotes_or_var(arr->arr[i]))
			tmp = expand_line(arr->arr[i], sh);
		else
			tmp = cmd_elaborate_line(arr->arr[i], sh);
		if (!tar_merge_strarr(tar, tmp))
			return (tar_free(tar), tar_free(tmp), NULL);
		tar_free(tmp);
		i++;
	}
	return (tar);
}
