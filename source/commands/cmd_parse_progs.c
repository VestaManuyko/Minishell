/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_progs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:06:57 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/24 11:21:21 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	cmd_parse_progs(t_prog *proc, t_arr *env)
{
	t_arr	*tar;
	char	**arr;

	arr = clear_dollar((char **)proc->prog->arr, env);
	if (arr == NULL)
		return (0);
	tar_free(proc->prog);
	tar = tar_init(arr, free);
	arr_free(arr);
	if (tar == NULL)
		return (0);
	proc->prog = tar;
	return (1);
}
