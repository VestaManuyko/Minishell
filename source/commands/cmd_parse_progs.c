/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_progs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpaglia <fpaglia@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:06:57 by fpaglia           #+#    #+#             */
/*   Updated: 2025/11/25 12:42:20 by fpaglia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_strings.h"
#include <minishell.h>

int	cmd_parse_progs(t_prog *proc, t_arr *env)
{
	t_arr	*tar;

	if (proc->prog->size == 0)
		return (1);
	if (ft_strncmp((char *)proc->prog->arr[0], "export", 6) == 0)
		tar = cmd_expand_export(proc->prog, env);
	else
		tar = cmd_expand_prog(proc->prog, env);
	if (tar == NULL)
		return (0);
	tar_free(proc->prog);
	proc->prog = tar;
	return (1);
}
