/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_progs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:06:57 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/18 16:11:44 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_strings.h"
#include <minishell.h>

static char	**clear_dollar(char **arr, t_arr *env)
{
	char	*line;
	char	*line_d;
	char	**arr_in;
	char	**arr_out;

	arr_in = arr_deepcpy(arr);
	line = arr_to_str(arr_in, 1);
	if (line == NULL)
		return (0);
	line_d = str_expand(dollar, env, line, 1);
	free(line);
	if (line_d == NULL)
		return (0);
	arr_out = str_split_by_set(line_d, MS_BLANKS, 1);
	free(line_d);
	if (arr_out == NULL)
		return (NULL);
	return (arr_out);
}

static int	clear_quotes(char **arr, t_arr *env)
{
	int		i;
	char	*line;

	i = 0;
	while (arr[i] != NULL)
	{
		line = str_expand(quotes, env, arr[i], 0);
		if (line == NULL)
			return (0);
		free(arr[i]);
		arr[i] = line;
		i++;
	}
	return (1);
}

int	cmd_parse_progs(t_prog *proc, t_arr *env)
{
	t_arr	*tar;
	char	**arr;

	if (ft_strncmp((char *)proc->prog->arr[0], "export", 6))
		return (1);
	arr = clear_dollar((char **)proc->prog->arr, env);
	if (arr == NULL)
		return (0);
	if (!clear_quotes(arr, env))
		return (arr_free(arr), 0);
	tar_free(proc->prog);
	tar = tar_init(arr, free);
	arr_free(arr);
	if (tar == NULL)
		return (0);
	proc->prog = tar;
	return (1);
}
