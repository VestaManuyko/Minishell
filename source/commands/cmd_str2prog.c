/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_str2prog.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:10:47 by fpaglia           #+#    #+#             */
/*   Updated: 2025/10/23 15:55:52 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char **expand_dollar(char **arr, t_arr *env)
{
	char *line;
	char *line_d;
	char **arr_in;
	char **arr_out;
	
	arr_in = arr_deepcpy(arr);
	line = arr_to_str(arr_in);
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

int cmd_parse_progs(t_prog *proc, t_arr *env)
{
	t_arr	*tar;
	char	**arr;
	
	arr = expand_dollar((char **)proc->prog->arr, env);
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

int	cmd_str2prog(t_prog *proc, char *str, t_shell *sh)
{
	proc->redirect = tar_init(NULL, red_free);
	if (proc->redirect == NULL)
		return (0);
	proc->prog = tar_init(NULL, free);
	if (proc->prog == NULL)
		return (0);
	if (!cmd_split_tokens(proc, str, proc->redirect))
		return (0);
	if (!cmd_parse_redirect(proc->redirect, proc, sh->env))
		return (0);
	// if (!cmd_parse_progs(proc, sh->env))
	// 	return (0);
	return (1);
}
