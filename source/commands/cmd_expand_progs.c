/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand_progs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:33:49 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/24 12:34:50 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	quotes_or_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	if (ft_strchr(str, '$') != NULL)
		return (1);
	return (0);
}

t_arr	*cmd_expand_prog(t_arr *arr, t_arr *env)
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
		{
			if (!tar_putstr(tar, arr->arr[i]))
				return (tar_free(tar), NULL);
		}
		else
		{
			tmp = cmd_elaborate_line(arr->arr[i], env);
			if (!tar_merge_strarr(tar, tmp))
				return (tar_free(tar), tar_free(tmp), NULL);
			tar_free(tmp);
		}
		i++;
	}
	return (tar);
}
